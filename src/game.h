#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <algorithm>
#include "SDL.h"

#include "controller.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"


class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize();

 private:
  Player player;
  std::shared_ptr<Enemy> enemy;
  std::vector<std::shared_ptr<Bullet>> _bullets;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif