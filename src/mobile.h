#ifndef MOBILE_H
#define MOBILE_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include "gameObject.h"


class Mobile : public GameObject {
 public:
  enum class Direction { kNoop, kUp, kDown, kLeft, kRight };

  Mobile(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
         std::size_t init_x, std::size_t init_y, std::size_t size);

  void Update();

  void setHp(int hp);
  void getHp(int &hp);

  void setDirection(Direction direction);
  Direction getDirection();

  void toggleAlive();
  bool isAlive();

 protected:
  bool _alive = true;  
  int _hp;
  float _speed;
  Direction _direction = Direction::kUp;
  void UpdatePos(); 

 private:
};

#endif