#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include "gameObject.h"


class Player : public GameObject {
 public:
  Player(int grid_width, int grid_height) {
    std::cout << "Player Constructor" << std::endl;

    //_grid_width = grid_width;
    //_grid_height = grid_height;
    setGridSize(grid_width, grid_height);

    //_pos_x = grid_width / 2;
    //_pos_y = grid_height / 2;
    setPosition(grid_width / 2, grid_height / 2);
  }

  void Update();

  //void GrowBody();
  //bool PlayerCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  //float head_x;
  //float head_y;
  //std::vector<SDL_Point> body;

 private:
  void UpdatePos();
  //void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  //bool growing{false};
  //int grid_width;
  //int grid_height;
};

#endif