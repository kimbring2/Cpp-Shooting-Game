#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "SDL.h"
#include "mobile.h"


class Enemy : public Mobile, public std::enable_shared_from_this<Enemy> {
 public:
  Enemy(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
        std::size_t init_x, std::size_t init_y, std::size_t size);

  Direction direction = Direction::kUp;

  void simulate();
 
  // miscellaneous
  std::shared_ptr<Enemy> get_shared_this() { return shared_from_this(); }

 protected:
  //std::vector<std::thread> threads;
  std::thread thread;

 private:
  // typical behaviour methods
  void cycleThroughPhases();
};

#endif