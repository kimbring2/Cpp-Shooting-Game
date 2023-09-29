#include "bullet.h"
#include "boss.h"
#include <cmath>
#include <iostream>


std::mutex Bullet::_mtx;

Bullet::Bullet(float speed, std::size_t screen_width, std::size_t screen_height, 
               std::size_t init_x, std::size_t init_y, std::size_t size, bool mine,
               Direction direction) 
  : GameObject(screen_width, screen_height, init_x, init_y, size), _mine(mine), 
    _speed(speed), _direction(direction) {
  //std::cout << "Bullet Constructor" << std::endl;
}


Bullet::~Bullet() {
  //std::cout << "Bullet Destructor" << std::endl;
  t.join();
}


void Bullet::copyPlayer(const std::shared_ptr<Player>& source) {
  // Copy the vector of player to this class
  player = source;
}


void Bullet::copyEnemyVector(const std::vector<std::shared_ptr<Enemy>>& sourceVector) {
  // Copy the vector of enemy to this class
  _enemies = sourceVector;
}


void Bullet::copyFixedEnemyVector(const std::vector<std::shared_ptr<FixedEnemy>>& sourceVector) {
  // Copy the vector of enemy to this class
  _fixedEnemies = sourceVector;
}


void Bullet::copyBossVector(const std::vector<std::shared_ptr<Boss>>& sourceVector) {
  //Copy the vector of enemy to this class
  _bosses = sourceVector;
}


void Bullet::simulate() {
  // launch drive function in a thread
  //threads.emplace_back(std::thread(&Enemy::cycleThroughPhases, this)); 
  t = std::thread(&Bullet::cycleThroughPhases, this);
}


double Bullet::distanceBetweenTwoPoints(int x, int y, int a, int b) {
  return sqrt(pow(x - a, 2) + pow(y - b, 2));
}


// virtual function which is executed in a thread
void Bullet::cycleThroughPhases() {
  // initalize variables
  double cycleDuration = 10 * (rand() % 2 + 4); // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  // init stop watch
  lastUpdate = std::chrono::system_clock::now();
  while (!_destroyed) {
    //std::cout << "Bullet, cycleThroughPhases" << std::endl;

    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // compute time difference to stop watch
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - \
        lastUpdate).count();

    if (timeSinceLastUpdate >= cycleDuration) {
      //std::cout << "Bullet, cycleThroughPhases" << std::endl;
      int pos_x, pos_y; 
      getPosition(pos_x, pos_y);

      switch (_direction) {
        case Direction::kUp:
          //std::cout << "Direction::kUp" << std::endl;
          pos_y -= _speed;
          break;
        case Direction::kDown:
          //std::cout << "Direction::kDown" << std::endl;
          pos_y += _speed;
          break;
        case Direction::kLeft:
          //std::cout << "Direction::kLeft" << std::endl;
          pos_x -= _speed;
          break;
        case Direction::kRight:
          //std::cout << "Direction::kRight" << std::endl;
          pos_x += _speed;
          break;
      }

      setPosition(pos_x, pos_y);

      lastUpdate = std::chrono::system_clock::now();

      // Collsion detection with player
      if (!getMine()) {
        std::unique_lock<std::mutex> lck(_mtx);
        int player_pos_x, player_pos_y;
        player->getPosition(player_pos_x, player_pos_y);
        int player_hp = player->getHp();
        int player_size = player->getSize();
        float distance_player = distanceBetweenTwoPoints(player_pos_x, player_pos_y, 
                                                         _pos_x, _pos_y);
        float collision_dis_player = getSize() + player_size;
        if (distance_player <= collision_dis_player * 5) {
          // Player collision with bullet
          _destroyed = true;
          if (player_hp > 10) {
            player->setHp(player_hp - 10);
          } else {
            //std::cout << "enemy die" << std::endl;
            player->toggleAlive();
          }
        }
        lck.unlock();
      }

      // Collsion detection with enemy
      if (getMine()) {
        std::unique_lock<std::mutex> lck(_mtx);
        for (auto it_e = _enemies.begin(); it_e != _enemies.end();) {
          int enemy_pos_x, enemy_pos_y; 
          (*it_e)->getPosition(enemy_pos_x, enemy_pos_y);
          int enemy_size = (*it_e)->getSize();
          int enemy_hp = (*it_e)->getHp();

          float distance_enemy = distanceBetweenTwoPoints(enemy_pos_x, enemy_pos_y, 
                                                          _pos_x, _pos_y);
          float collision_dis_enemy = getSize() + enemy_size;

          if (distance_enemy <= collision_dis_enemy * 5) {
            // Enemy collision with bullet
            _destroyed = true;
            if (enemy_hp > 10) {
              (*it_e)->setHp(enemy_hp - 10);
            } else {
              //std::cout << "enemy die" << std::endl;
              (*it_e)->toggleAlive();
            }
          }
          
          it_e++;
        }
        lck.unlock();
      }

      // Collsion detection with fixed enemy
      if (getMine()) {
        std::unique_lock<std::mutex> lck(_mtx);
        for (auto it_fe = _fixedEnemies.begin(); it_fe != _fixedEnemies.end();) {
          int fixed_enemy_pos_x, fixed_enemy_pos_y; 
          (*it_fe)->getPosition(fixed_enemy_pos_x, fixed_enemy_pos_y);
          int fixed_enemy_size = (*it_fe)->getSize();
          int fixed_enemy_hp = (*it_fe)->getHp();

          float distance_fixed_enemy = distanceBetweenTwoPoints(fixed_enemy_pos_x, 
                                                                fixed_enemy_pos_y, 
                                                                _pos_x, _pos_y);
          float collision_dis_fixed_enemy = getSize() + fixed_enemy_size;

          if (distance_fixed_enemy <= collision_dis_fixed_enemy * 5) {
            // Enemy collision with bullet
            _destroyed = true;
            if (fixed_enemy_hp > 10) {
              (*it_fe)->setHp(fixed_enemy_hp - 10);
            } else {
              //std::cout << "enemy die" << std::endl;
              (*it_fe)->toggleAlive();
            }
          }
          
          it_fe++;
        }
        lck.unlock();
      }

      // Collsion detection with fixed enemy
      if (getMine()) {
        std::unique_lock<std::mutex> lck(_mtx);
        for (auto it_b = _bosses.begin(); it_b != _bosses.end();) {
          int boss_pos_x, boss_pos_y; 
          (*it_b)->getPosition(boss_pos_x, boss_pos_y);
          int boss_size = (*it_b)->getSize();
          int boss_hp = (*it_b)->getHp();

          float distance_boss = distanceBetweenTwoPoints(boss_pos_x, 
                                                         boss_pos_y, 
                                                         _pos_x, _pos_y);
          float collision_dis_boss = getSize() + boss_size;

          if (distance_boss <= collision_dis_boss * 5) {
            // Boss collision with bullet
            _destroyed = true;
            if (boss_hp > 10) {
              (*it_b)->setHp(boss_hp - 10);
            } else {
              //std::cout << "enemy die" << std::endl;
              (*it_b)->toggleAlive();
            }
          }
          
          it_b++;
        }
        lck.unlock();
      }

      if ( (_pos_y < 0) || (_pos_y > _screen_height) ) {
        _destroyed = true;
      }
    }
  }
}