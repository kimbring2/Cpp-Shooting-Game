#include "bomb.h"
#include <cmath>
#include <iostream>


std::mutex Bomb::_mtx;

Bomb::Bomb(float speed, std::size_t screen_width, std::size_t screen_height, 
           std::size_t init_x, std::size_t init_y, std::size_t size, bool mine) 
  : Bullet(speed, screen_width, screen_height, init_x, init_y, size, mine)  {
  std::cout << "Bomb Constructor" << std::endl;
}


Bomb::~Bomb() {
  std::cout << "Bomb Destructor" << std::endl;
  t.join();
}


// virtual function which is executed in a thread
void Bomb::cycleThroughPhases() {
  // initalize variables
  double cycleDuration = 10 * (rand() % 2 + 4); // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  // init stop watch
  lastUpdate = std::chrono::system_clock::now();
  //while (true)
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
      }

      if ( (_pos_y < 0) || (_pos_y > _screen_height) ) {
        _destroyed = true;
      }
    }
  }
}