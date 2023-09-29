#ifndef BOSS_H
#define BOSS_H

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

#include "SDL.h"
#include "enemy.h"
#include "bullet.h"

class Bullet;

class Boss : public Enemy {
 public:
  Boss(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
       std::size_t init_x, std::size_t init_y, std::size_t size);
  //~Boss();

 //void simulate() override;
 
 protected:

 private:
  // typical behaviour methods
  void cycleThroughPhases() override;
};

#endif