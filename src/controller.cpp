#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "player.h"


void Controller::ChangeDirection(Player &player, Player::Direction input,
                                 Player::Direction opposite) const {
  if (player.direction != opposite || player.size == 1) player.direction = input;
  return;
}


void Controller::HandleInput(bool &running, Player &player) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    //std::cout << "e.type" << e.type << std::endl;

    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      std::cout << "e.key.keysym.sym" << e.key.keysym.sym << std::endl;
      
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
      }
    }
  }
}