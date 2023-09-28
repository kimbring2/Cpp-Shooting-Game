#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include <thread>
#include "SDL.h"
#include "mobile.h"


class Player : public Mobile, public std::enable_shared_from_this<Player> {
 public:
  Player(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
         std::size_t init_x, std::size_t init_y, std::size_t size, std::size_t bomb_count);

  void setBombCount(int count) { _bomb_count = count; };
  int getBombCount() { return _bomb_count; };

 protected:
  int _bomb_count; 

 private:

};

#endif