#include "bomb.h"
#include "bullet.h"
#include <cmath>
#include <iostream>


//std::mutex Bomb::_mtx;

Bomb::Bomb(float speed, std::size_t screen_width, std::size_t screen_height, 
           std::size_t init_x, std::size_t init_y, std::size_t size, bool mine,
           float timer, Direction direction) 
  : Bullet(speed, screen_width, screen_height, init_x, init_y, size, mine, direction), _timer(timer) {
  std::cout << "Bomb Constructor" << std::endl;
}


//Bomb::~Bomb() {
//  std::cout << "Bomb Destructor" << std::endl;
  //t.join();
//}


/*
void Bomb::copyPlayer(const std::shared_ptr<Player>& source) {
  // Copy the vector of player to this class
  player = source;
}


void Bomb::copyEnemyVector(const std::vector<std::shared_ptr<Enemy>>& sourceVector) {
  // Copy the vector of enemy to this class
  _enemies = sourceVector;
}


void Bomb::copyFixedEnemyVector(const std::vector<std::shared_ptr<FixedEnemy>>& sourceVector) {
  // Copy the vector of enemy to this class
  _fixedEnemies = sourceVector;
}


void Bomb::copyBossVector(const std::vector<std::shared_ptr<Boss>>& sourceVector) {
  //Copy the vector of enemy to this class
  _bosses = sourceVector;
}


double Bomb::distanceBetweenTwoPoints(int x, int y, int a, int b) {
  return sqrt(pow(x - a, 2) + pow(y - b, 2));
}
*/


void Bomb::simulate() {
  // launch drive function in a thread
  //threads.emplace_back(std::thread(&Enemy::cycleThroughPhases, this)); 
  t = std::thread(&Bomb::cycleThroughPhases, this);
}


// virtual function which is executed in a thread
void Bomb::cycleThroughPhases() {
  // initalize variables
  double cycleDuration = 10 * (rand() % 2 + 4); // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  // init stop watch
  lastUpdate = std::chrono::system_clock::now();
  while (!_destroyed) {
    //std::cout << "Bomb, cycleThroughPhases" << std::endl;

    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // compute time difference to stop watch
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - \
        lastUpdate).count();

    if (timeSinceLastUpdate >= cycleDuration) {
      std::cout << "Bomb, cycleThroughPhases" << std::endl;

      lastUpdate = std::chrono::system_clock::now();

      if (_timer > 15) {
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
        }

        setPosition(pos_x, pos_y);
      } else if (_timer == 15) {
        //std::cout << "_timer" << _timer << std::endl;
        if (_timer == 15) {
          setSize(20);
        }
      } else if (_timer < 15) {
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

            if (distance_enemy <= collision_dis_enemy * 10) {
              // Enemy collision with Bomb
              _destroyed = true;
              (*it_e)->toggleAlive();
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

            if (distance_fixed_enemy <= collision_dis_fixed_enemy * 10) {
              // Fixed enemy collision with Bomb
              _destroyed = true;
              (*it_fe)->toggleAlive();
            }
            
            it_fe++;
          }
          lck.unlock();
        }
      }

      if ( (_pos_y < 0) || (_pos_y > _screen_height) ) {
        _destroyed = true;
      }

      if (_timer > 0) {
        _timer -= 1;
      } else {
        _destroyed = true;
      }
    }
  }
}