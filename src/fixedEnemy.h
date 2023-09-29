#ifndef FIXEDENEMY_H
#define FIXEDENEMY_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "SDL.h"
#include "enemy.h"
//#include "bullet.h"


class Bullet;


class FixedEnemy : public Enemy {
 public:
  FixedEnemy(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
             std::size_t init_x, std::size_t init_y, std::size_t size);
  //~FixedEnemy();

  //void simulate();
 
  // miscellaneous
  //std::shared_ptr<FixedEnemy> get_shared_this() { return shared_from_this(); }

  //bool _bulletSpawned = false;
  //Bullet *_bullet;

 protected:
  //std::vector<std::thread> threads;
  //std::thread t;

 private:
  // typical behaviour methods
  void cycleThroughPhases() override;
};

#endif