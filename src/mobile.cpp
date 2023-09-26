#include "mobile.h"
#include <cmath>
#include <iostream>


Mobile::Mobile(int hp, float speed, std::size_t screen_width, std::size_t screen_height,
               std::size_t init_x, std::size_t init_y, std::size_t size) 
  : GameObject(screen_width, screen_height, init_x, init_y, size), _hp(hp), _speed(speed)  {
  std::cout << "Mobile Constructor" << std::endl;
}


void Mobile::Update() {
  int pos_x, pos_y; 
  getPosition(pos_x, pos_y);

  SDL_Point prev_cell{static_cast<int>(pos_x), static_cast<int>(pos_y)};  // We first capture the head's cell before updating.
  UpdatePos();
  SDL_Point current_cell{static_cast<int>(pos_x), static_cast<int>(pos_y)};  // Capture the head's cell after updating.
}


void Mobile::UpdatePos() {
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

    case Direction::kLeft:
      //std::cout << "Direction::kLeft" << std::endl;
      pos_x -= _speed;
      break;

    case Direction::kRight:
      //std::cout << "Direction::kRight" << std::endl;
      pos_x += _speed;
      break;
  }

  if (_move_inertia == 0) {
    setDirection(Direction::kNoop);
  } else {
    _move_inertia -= 1;
  }

  // Check player is out of screen x 
  if (pos_x < 0) {
    pos_x = 0;
  } else if (pos_x > _screen_height) {
    pos_x = _screen_height;
  }

  // Check player is out of screen y
  if (pos_y < 0) {
    pos_y = 0;
  } else if (pos_y > _screen_width) {
    pos_y = _screen_width;
  }

  setPosition(pos_x, pos_y);
}


void Mobile::toggleAlive() {
  _alive = !_alive;
}


bool Mobile::isAlive() {
  return _alive;
}


void Mobile::setHp(int hp) {
  _hp = hp;
}


int Mobile::getHp() {
  return _hp;
}


void Mobile::setDirection(Mobile::Direction direction) {
  _direction = direction;
}


Mobile::Direction Mobile::getDirection() {
  return _direction;
}

void Mobile::setMoveInertia(int inertia) {
  _move_inertia = inertia;
}

int Mobile::getMoveInertia() {
  return _move_inertia;
}