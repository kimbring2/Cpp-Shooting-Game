#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "SDL.h"


enum ObjectType
{
    noObject,
    objectPlayer,
    objectEnemy,
    objectItem,
};


class GameObject {
 public:
  // constructor / desctructor
  GameObject(std::size_t screen_width, std::size_t screen_height,
             std::size_t init_x, std::size_t init_y, std::size_t size);
  //~GameObject();

  // getter and setter
  int getSize() { return _size; }
  void setSize(int size) { _size = size; }

  void setPosition(int x, int y);
  void getPosition(int &x, int &y);

  virtual void Update() {};

  bool GameObjectCell(int x, int y);

  // Copy and move assignment constructor
  GameObject(const GameObject &source);
  GameObject& operator=(const GameObject &source);
  GameObject(GameObject &&source);
  GameObject& operator=(GameObject &&source);

 protected:
  int _pos_x, _pos_y;               // object position in pixels
  int _screen_height, _screen_width;
  int _size{1};

  virtual void UpdatePos() {};

 private:
};

#endif