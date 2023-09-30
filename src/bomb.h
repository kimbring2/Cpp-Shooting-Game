#ifndef BOMB_H
#define BOMB_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include <thread>
#include <mutex>

#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "fixedEnemy.h"
#include "boss.h"

class Player;
class Enemy;
class FixedEnemy;
class Boss;

class Bomb : public Bullet {
 public:
  Bomb(float speed, std::size_t screen_width, std::size_t screen_height, 
       std::size_t init_x, std::size_t init_y, std::size_t size, bool mine,
       float timer, Direction direction);

  void simulate() override;

 protected:
  float _timer;

 private:
  void cycleThroughPhases() override;
};

#endif