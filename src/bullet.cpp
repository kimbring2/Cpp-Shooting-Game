#include "bullet.h"
#include <cmath>
#include <iostream>


Bullet::Bullet(float speed, std::size_t screen_width, std::size_t screen_height, 
               std::size_t init_x, std::size_t init_y, std::size_t size, bool mine) 
  : GameObject(screen_width, screen_height, init_x, init_y, size), _speed(speed)  {
  std::cout << "Bullet Constructor" << std::endl;

  if (mine == true) {
    _direction = Direction::kUp;
  }
  else {
    _direction = Direction::kDown;
  }
}


Bullet::~Bullet() {
  std::cout << "Bullet Destructor" << std::endl;
  t.join();
}


void Bullet::simulate()
{
    // launch drive function in a thread
    //threads.emplace_back(std::thread(&Enemy::cycleThroughPhases, this)); 
    t = std::thread(&Bullet::cycleThroughPhases, this);
}


// virtual function which is executed in a thread
void Bullet::cycleThroughPhases()
{
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

        if (timeSinceLastUpdate >= cycleDuration)
        {
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

            //if (pos_y < 0) {
            //  pos_y = 0;
            //} else if (pos_y > _screen_width) {
            //  pos_y = _screen_width;
            //}

            setPosition(pos_x, pos_y);

            //UpdatePos();
            lastUpdate = std::chrono::system_clock::now();
        }
    }
}