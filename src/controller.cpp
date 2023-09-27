#include "controller.h"
#include <iostream>
#include <chrono>
#include "SDL.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"


void Controller::ChangeDirection(std::shared_ptr<Player> player, Player::Direction input,
                                 Mobile::Direction opposite) const {
  if (player->getDirection() != opposite) {
    //player->setDirection(input);
  }

  player->setDirection(input);

  return;
}


void Controller::HandleInput(bool &running, std::shared_ptr<Player> player) {
  SDL_Event e;

  const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);

  SDL_PollEvent(&e);

  // Exit game
  if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
    running = false;
  }

  // Up, Down, Left, Right movement
  if (keyboard_state_array[SDL_SCANCODE_UP]) {
    ChangeDirection(player, Player::Direction::kUp, Player::Direction::kDown);
  }
  if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
    ChangeDirection(player, Player::Direction::kDown, Player::Direction::kUp);
  }
  if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
    ChangeDirection(player, Player::Direction::kLeft, Player::Direction::kRight);
  }
  if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
    ChangeDirection(player, Player::Direction::kRight, Player::Direction::kLeft);
  }

  // Shot bullet
  if (keyboard_state_array[SDL_SCANCODE_A]) {
    int pos_x, pos_y; 
    player->getPosition(pos_x, pos_y);

    if (_bullet_timer == 0) {
      // Set new bullet information before sending to the game.cpp
      _bullet_x = pos_x;
      _bullet_y = pos_y;
      _bullet_mine = true;
      _bulletSpawned = true;

      _bullet_timer = 10;
    }
  }

  // Shot bomb
  if (keyboard_state_array[SDL_SCANCODE_B]) {
    int pos_x, pos_y; 
    player->getPosition(pos_x, pos_y);

    // Set new bullet information before sending to the game.cpp
    _bomb_x = pos_x;
    _bomb_y = pos_y;
    _bomb_mine = true;
    _bombSpawned = true;
  }

  if (_bullet_timer > 0) {
    _bullet_timer -= 1;
  }
}