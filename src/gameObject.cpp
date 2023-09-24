#include <cmath>
#include <iostream>
#include "gameObject.h"


GameObject::GameObject(std::size_t screen_width, std::size_t screen_height,
                       std::size_t init_x, std::size_t init_y, std::size_t size) {
  std::cout << "GameObject Constructor" << std::endl;
  _screen_width = screen_width;
  _screen_height = screen_height;
  _pos_x = init_x;
  _pos_y = init_y;
  _size = size;
}


void GameObject::setPosition(int x, int y) {
    _pos_x = x;
    _pos_y = y;
}


void GameObject::getPosition(int &x, int &y) {
    x = _pos_x;
    y = _pos_y;
}


// Inefficient method to check if cell is occupied by GameObject.
bool GameObject::GameObjectCell(int x, int y) {

  if (x == static_cast<int>(_pos_x) && y == static_cast<int>(_pos_y)) {
    return true;
  }

  return false;
}