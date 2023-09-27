#ifndef BOMB_H
#define BOMB_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include <thread>
#include <mutex>

#include "gameObject.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

class Player;
class Enemy;
class Bullet;

class Bomb : public Bullet {
 public:
  Bomb(float speed, std::size_t screen_width, std::size_t screen_height, 
       std::size_t init_x, std::size_t init_y, std::size_t size, bool mine);
  ~Bomb();

 protected:
  //std::thread t;
  static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

 private:
  void cycleThroughPhases();
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>> _enemies;
};

#endif