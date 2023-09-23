#include "player.h"
#include <cmath>
#include <iostream>


void Player::Update() {
  float pos_x, pos_y; 
  getPosition(&pos_x, &pos_y);

  SDL_Point prev_cell{static_cast<int>(pos_x), static_cast<int>(pos_y)};  // We first capture the head's cell before updating.
  UpdatePos();
  SDL_Point current_cell{static_cast<int>(pos_x), static_cast<int>(pos_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the Player head has moved to a new cell.
  //if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
  //  UpdateBody(current_cell, prev_cell);
  //}
}


void Player::UpdatePos() {
  float pos_x, pos_y; 
  getPosition(&pos_x, &pos_y);

  switch (direction) {
    case Direction::kUp:
      pos_y -= speed;
      break;

    case Direction::kDown:
      pos_y += speed;
      break;

    case Direction::kLeft:
      pos_x -= speed;
      break;

    case Direction::kRight:
      pos_x += speed;
      break;
  }

  // Wrap the Player around to the beginning if going off of the screen.
  pos_x = fmod(pos_x + grid_width, grid_width);
  pos_y = fmod(pos_y + grid_height, grid_height);

  setPosition(&pos_x, &pos_y);
}


/*
void Player::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the Player has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}
*/


//void Player::GrowBody() { growing = true; }


/*
// Inefficient method to check if cell is occupied by Player.
bool Player::PlayerCell(int x, int y) {
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
*/