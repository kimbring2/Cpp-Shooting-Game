#include "player.h"
#include <cmath>
#include <iostream>


Player::Player(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
               std::size_t init_x, std::size_t init_y, std::size_t size) 
  : Mobile(hp, speed, screen_width, screen_height, init_x, init_y, size) {
  std::cout << "Player Constructor" << std::endl;
}
