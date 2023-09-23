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
  enum class Direction { kUp, kDown, kLeft, kRight };

  // constructor / desctructor
  GameObject();
  //~GameObject();

  // getter and setter
  int getID() { return _id; }
  void setPosition(float x, float y);
  void getPosition(float &x, float &y);
  ObjectType getType() { return _type; }
  void setGridSize(int x, int y);
  void getGridSize(int &x, int &y);

  virtual void Update() {};

  bool GameObjectCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  //float pos_x;
  //float pos_y;
  //std::vector<SDL_Point> body;

 private:
  ObjectType _type;                 // identifies the class type
  int _id;                          // every game object has its own unique id
  float _pos_x, _pos_y;               // object position in pixels

  virtual void UpdatePos() {};
  //virtual void UpdateBody() {};

  //bool growing{false};
  int _grid_width;
  int _grid_height;
};

#endif