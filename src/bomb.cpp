#include "bomb.h"
#include <cmath>
#include <iostream>


std::mutex Bomb::_mtx;

Bomb::Bomb(float speed, std::size_t screen_width, std::size_t screen_height, 
           std::size_t init_x, std::size_t init_y, std::size_t size, bool mine) 
  : Bullet(speed, screen_width, screen_height, init_x, init_y, size, mine)  {
  std::cout << "Bomb Constructor" << std::endl;

  if (mine == true) {
    _direction = Direction::kUp;
  }
  else {
    _direction = Direction::kDown;
  }

  _mine = mine;
}


Bomb::~Bomb() {
  std::cout << "Bomb Destructor" << std::endl;
  t.join();
}


void Bomb::simulate() {
  // launch drive function in a thread
  //threads.emplace_back(std::thread(&Enemy::cycleThroughPhases, this)); 
  t = std::thread(&Bomb::cycleThroughPhases, this);
}


void Bomb::copyPlayer(const std::shared_ptr<Player>& source) {
  // Copy the vector of player to this class
  player = source;
}


void Bomb::copyEnemyVector(const std::vector<std::shared_ptr<Enemy>>& sourceVector) {
  // Copy the vector of enemy to this class
  _enemies = sourceVector;
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
      //std::cout << "Bomb, cycleThroughPhases" << std::endl;

      int pos_x, pos_y; 
      getPosition(pos_x, pos_y);

      //std::cout << "pos_x: " << pos_x << "pos_y: " << pos_y << std::endl;

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

      lastUpdate = std::chrono::system_clock::now();

      //std::cout << "getMine(): " << getMine() << std::endl;

      // Collsion detection with enemy
      for (auto it_e = _enemies.begin(); it_e != _enemies.end();) {
        int enemy_pos_x, enemy_pos_y; 
        (*it_e)->getPosition(enemy_pos_x, enemy_pos_y);
        int enemy_size = (*it_e)->getSize();
        int enemy_hp = (*it_e)->getHp();

        float distance_enemy = distanceBetweenTwoPoints(enemy_pos_x, enemy_pos_y, 
                                                        _pos_x, _pos_y);
        float collision_dis_enemy = getSize() + enemy_size;

        //std::cout << "distance_enemy: " << distance_enemy << std::endl;
        //std::cout << "collision_dis_enemy: " << collision_dis_enemy << std::endl;

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

      if ( (_pos_y < 0) || (_pos_y > _screen_height) ) {
        std::cout << "bomb _destroyed" << std::endl;
        _destroyed = true;
      }
    }
  }
}