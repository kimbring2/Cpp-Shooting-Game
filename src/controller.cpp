#include "controller.h"
#include <iostream>
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
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(player, Player::Direction::kUp,
                          Player::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(player, Player::Direction::kDown,
                          Player::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(player, Player::Direction::kLeft,
                          Player::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(player, Player::Direction::kRight,
                          Player::Direction::kLeft);
          break;
        case SDLK_a:
          // shot bullet
          int pos_x, pos_y; 
          player->getPosition(pos_x, pos_y);

          // Set new bullet information before sending to the game.cpp
          _bullet_x = pos_x;
          _bullet_y = pos_y;
          _bullet_mine = true;
          _bulletSpawned = true;

          break;
      }
    }
  }
}