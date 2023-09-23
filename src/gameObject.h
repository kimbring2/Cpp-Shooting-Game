#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "SDL.h"

class GameObject {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  // constructor / desctructor
  GameObject();
  //~GameObject();

  virtual void Update() {};

  void GrowBody();
  bool GameObjectCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  virtual void UpdateHead() {};
  virtual void UpdateBody() {};

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif