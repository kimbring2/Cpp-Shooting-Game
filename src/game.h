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
#include "bomb.h"
#include "fixedEnemy.h"


class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  ~Game();

  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize();

 private:
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>> _enemies;
  std::vector<std::shared_ptr<Bullet>> _bullets;
  std::vector<std::shared_ptr<Bomb>> _bombs;
  std::vector<std::shared_ptr<FixedEnemy>> _fixedEnemies;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();
};

#endif