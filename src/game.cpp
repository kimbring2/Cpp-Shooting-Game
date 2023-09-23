#include "game.h"
#include <iostream>
#include "SDL.h"


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : player(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)), random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}


void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    //std::cout << "frame_count: " << frame_count << std::endl;

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);
    Update();
    renderer.Render(player, food);

    frame_end = SDL_GetTicks();

    //std::cout << "title_timestamp: " << title_timestamp << ", frame_end: " << frame_end << std::endl;

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      //std::cout << "frame_end - title_timestamp >= 1000" << std::endl;

      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller than the target ms_per_frame), 
    // delay the loop to achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}


void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);

    // Check that the location is not occupied by a player item before placing food.
    if (!player.GameObjectCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}


void Game::Update() {
  if (!player.alive) return;

  player.Update();

  float pos_x, pos_y; 
  player.getPosition(&pos_x, &pos_y);

  int new_x = static_cast<int>(pos_x);
  int new_y = static_cast<int>(pos_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();

    // Grow snake and increase speed.
    //player.GrowBody();
    //player.speed += 0.02;
  }
}


int Game::GetScore() const { return score; }
int Game::GetSize() const { return player.size; }