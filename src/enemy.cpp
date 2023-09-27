#include "mobile.h"
#include "enemy.h"
#include <cmath>
#include <iostream>
#include <thread>


Enemy::Enemy(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
             std::size_t init_x, std::size_t init_y, std::size_t size) 
  : Mobile(hp, speed, screen_width, screen_height, init_x, init_y, size) {
  //std::cout << "Enemy Constructor" << std::endl;
}


Enemy::~Enemy() {
  //std::cout << "Enemy Destructor" << std::endl;
  t.join();
}


void Enemy::simulate() {
  // launch drive function in a thread
  //threads.emplace_back(std::thread(&Enemy::cycleThroughPhases, this)); 
  t = std::thread(&Enemy::cycleThroughPhases, this);
}


// virtual function which is executed in a thread
void Enemy::cycleThroughPhases() {
  // initalize variables
  double cycleDuration = 100 * (rand() % 2 + 4); // duration of a single simulation cycle in ms
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;

  // init stop watch
  lastUpdate = std::chrono::system_clock::now();

  int step = 0;
  while (_alive) {
    // sleep at every iteration to reduce CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    // compute time difference to stop watch
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - \
        lastUpdate).count();

    if (timeSinceLastUpdate >= cycleDuration) {
      int pos_x, pos_y; 
      getPosition(pos_x, pos_y);

      int direction_index = rand() % 4;
      switch (direction_index) {
        case 0:
          //std::cout << "Direction::kUp" << std::endl;
          pos_y -= _speed;
          break;
        case 1:
          //std::cout << "Direction::kDown" << std::endl;
          pos_y += _speed;
          break;
        case 3:
          //std::cout << "Direction::kLeft" << std::endl;
          pos_x -= _speed;
          break;
        case 4:
          //std::cout << "Direction::kRight" << std::endl;
          pos_x += _speed;
          break;
      }

      setPosition(pos_x, pos_y);

      lastUpdate = std::chrono::system_clock::now();
 
      // Fire bullet randomly
      int bullet_fire = rand() % 4;
      if (bullet_fire == 0) {
        _bullet = new Bullet(10, 640, 640, _pos_x, _pos_y, 1, false);
        _bulletSpawned = true;
      }
    }

    step += 1;
  }
}