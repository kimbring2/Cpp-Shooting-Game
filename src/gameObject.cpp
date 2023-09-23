#include <cmath>
#include <iostream>
#include "gameObject.h"


GameObject::GameObject()
{
  std::cout << "GameObject Constructor" << std::endl;
}

/*
GameObject::~GameObject()
{
  std::cout << "GameObject Destructor" << std::endl;
}
*/


void GameObject::setPosition(float x, float y)
{
    _posX = x;
    _posY = y;
}


void GameObject::getPosition(float &x, float &y)
{
    x = _posX;
    y = _posY;
}


void GameObject::setGridSize(int width, int height)
{
    _grid_width = width;
    _grid_height = height;
}


void GameObject::getPGridSize(int &width, int &height)
{
    width = _grid_width;
    height = _grid_height;
}


// Inefficient method to check if cell is occupied by GameObject.
bool GameObject::GameObjectCell(int x, int y) {
  if (x == static_cast<int>(pos_x) && y == static_cast<int>(pos_y)) {
    return true;
  }

  /*
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  */

  return false;
}