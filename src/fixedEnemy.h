#ifndef FIXED_ENEMY_H
#define FIXED_ENEMY_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "SDL.h"
#include "enemy.h"


class FixedEnemy : public Enemy {
 public:
  FixedEnemy(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
             std::size_t init_x, std::size_t init_y, std::size_t size);

 protected:

 private:
  void cycleThroughPhases() override;
};

#endif