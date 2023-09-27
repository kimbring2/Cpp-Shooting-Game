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

  if (keyboard_state_array[SDL_SCANCODE_ESCAPE]) {
    //std::cout << "SDL_SCANCODE_ESCAPE" << std::endl;
    running = false;
  }

  if (keyboard_state_array[SDL_SCANCODE_UP]) {
    //std::cout << "SDL_SCANCODE_UP" << std::endl;
    ChangeDirection(player, Player::Direction::kUp, Player::Direction::kDown);
  }

  if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
    //std::cout << "SDL_SCANCODE_DOWN" << std::endl;
    ChangeDirection(player, Player::Direction::kDown, Player::Direction::kUp);
  }

  if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
    //std::cout << "SDL_SCANCODE_LEFT" << std::endl;
    ChangeDirection(player, Player::Direction::kLeft, Player::Direction::kRight);
  }

  if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
    //std::cout << "SDL_SCANCODE_RIGHT" << std::endl;
    ChangeDirection(player, Player::Direction::kRight, Player::Direction::kLeft);
  }

  if (keyboard_state_array[SDL_SCANCODE_A]) {
    //std::cout << "SDL_SCANCODE_UP" << std::endl;
    int pos_x, pos_y; 
    player->getPosition(pos_x, pos_y);

    // Set new bullet information before sending to the game.cpp
    _bullet_x = pos_x;
    _bullet_y = pos_y;
    _bullet_mine = true;
    _bulletSpawned = true;
  }

  /*
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      //std::cout << "e.key.keysym.scancode: " << e.key.keysym.scancode << std::endl;

      if (keyboard_state_array[SDL_SCANCODE_UP]) {
        //std::cout << "SDL_SCANCODE_UP" << std::endl;
        ChangeDirection(player, Player::Direction::kUp, Player::Direction::kDown);
      }

      if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
        //std::cout << "SDL_SCANCODE_DOWN" << std::endl;
        ChangeDirection(player, Player::Direction::kDown, Player::Direction::kUp);
      }

      if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
        //std::cout << "SDL_SCANCODE_LEFT" << std::endl;
        ChangeDirection(player, Player::Direction::kLeft, Player::Direction::kRight);
      }

      if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
        //std::cout << "SDL_SCANCODE_RIGHT" << std::endl;
        ChangeDirection(player, Player::Direction::kRight, Player::Direction::kLeft);
      }
      
      if (keyboard_state_array[SDL_SCANCODE_A]) {
        //std::cout << "SDL_SCANCODE_A" << std::endl;
        // shot bullet
        int pos_x, pos_y; 
        player->getPosition(pos_x, pos_y);

        // Set new bullet information before sending to the game.cpp
        _bullet_x = pos_x;
        _bullet_y = pos_y;
        _bullet_mine = true;
        _bulletSpawned = true;
      }
    }
  }
  */
}