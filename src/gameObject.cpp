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


void GameObject::GrowBody() { growing = true; }


// Inefficient method to check if cell is occupied by GameObject.
bool GameObject::GameObjectCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }

  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }

  return false;
}