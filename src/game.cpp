#include "game.h"
#include <iostream>
#include <exception>
#include <cmath>
#include "SDL.h"


Game::Game(std::size_t screen_width, std::size_t screen_height)
    : engine(dev()),
      random_w(0, static_cast<int>(screen_width - 1)), 
      random_h(0, static_cast<int>(screen_height - 1)) {   
  player = std::make_shared<Player>(100, 10, screen_width, screen_height, 300, 590, 5, 3);

  _enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 100, 300, 5));
  _enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 120, 250, 5));
  _enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 379, 50, 5));
  _enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 250, 170, 5));

  _fixedEnemies.emplace_back(std::make_shared<FixedEnemy>(100, 10, screen_width, screen_height, 140, 170, 5));
  _fixedEnemies.emplace_back(std::make_shared<FixedEnemy>(100, 10, screen_width, screen_height, 500, 350, 5));
}


Game::~Game() {
  std::cout << "Game Destructor" << std::endl;

  player = NULL;
  delete player.get(); // delete the player

  // delete all enemies
  for (auto it = std::begin(_enemies); it != std::end(_enemies); ++it) {
    (*it)->toggleAlive();
    (*it) = NULL;
    delete it->get();
  }

  // delete all bullets
  for (auto it = std::begin(_bullets); it != std::end(_bullets); ++it) {
    (*it)->toggleDestroyed();
    (*it) = NULL;
    delete it->get();
  }

  // delete all bombs
  for (auto it = std::begin(_bombs); it != std::end(_bombs); ++it) {
    (*it)->toggleDestroyed();
    (*it) = NULL;
    delete it->get();
  }

  // delete all fixed enemies
  for (auto it = std::begin(_fixedEnemies); it != std::end(_fixedEnemies); ++it) {
    (*it)->toggleAlive();
    (*it) = NULL;
    delete it->get();
  }
}


void Game::Run(Controller &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // // Start the thread of enemy
  for (auto enemy : _enemies) {
    enemy->simulate();
  }

  // // Start the thread of fixed enemy
  for (auto fixedEnemy : _fixedEnemies) {
    fixedEnemy->simulate();
  }

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);

    // Check the player shot the bullet
    if (controller._bullet_spawned == true) {
      // Make the shared_ptr of generated bullet from player 
      std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(10, 640, 640, 
        controller._bullet_x, controller._bullet_y, 
        1, controller._bullet_mine, controller._bullet_direction);

      // Add bullet to vector
      _bullets.emplace_back(bullet);
      bullet->simulate(); // Start the thread of bullet

      controller._bullet_spawned = false; // reset the spawned flag
    }

    // Check the player shot the bomb
    if (controller._bomb_spawned == true) {
      //std::cout << "_bombs.size()" << _bombs.size() << std::endl;

      if (player->getBombCount() > 0) {
        if (_bombs.size() == 0) {
          std::shared_ptr<Bomb> bomb = std::make_shared<Bomb>(10, 640, 640, 
            controller._bomb_x, controller._bomb_y, 
             1, controller._bomb_mine, 40, controller._bomb_direction);

          _bombs.emplace_back(bomb);
          bomb->simulate(); // Start the thread of bomb

          // Decrease the bomb number
          player->setBombCount(player->getBombCount() - 1);
        }
      }

      controller._bomb_spawned = false; // reset the spawned flag
    }

    // Check the enemy shot the bullet
    // Use same way as player, but for multiple enemy
    for (auto _enemy : _enemies) {
      if (_enemy->_bulletSpawned == true) {
        _enemy->_bulletSpawned = false;
        _bullets.emplace_back(_enemy->_bullet);
        (_enemy->_bullet)->simulate();
      }
    }

    // Check the fixed enemy shot the bullet
    for (auto _fixedEnemy : _fixedEnemies) {
      if (_fixedEnemy->_bulletSpawned == true) {
        _fixedEnemy->_bulletSpawned = false;
        _bullets.emplace_back(_fixedEnemy->_bullet);
        (_fixedEnemy->_bullet)->simulate();
      }
    }

    // Delete the destroyed bullet
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), 
                   [](std::shared_ptr<Bullet> bullet) { 
                    return bullet->getDestroyed();
                   }), _bullets.end());

    // Delete the destroyed enemy
    _enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), 
                   [](std::shared_ptr<Enemy> enemy) { 
                    return !enemy->isAlive();
                   }), _enemies.end());

    // Delete the destroyed bomb
    _bombs.erase(std::remove_if(_bombs.begin(), _bombs.end(), 
                 [](std::shared_ptr<Bomb> bomb) { 
                    return bomb->getDestroyed();
                 }), _bombs.end());

    // Delete the destroyed fixed enemy
    _fixedEnemies.erase(std::remove_if(_fixedEnemies.begin(), _fixedEnemies.end(), 
                   [](std::shared_ptr<FixedEnemy> fixedEnemy) { 
                    return !fixedEnemy->isAlive();
                   }), _fixedEnemies.end());

    // Update the player, enemies infomation of bullet
    // it will be used for collision detection from thread of bullet 
    for (auto _bullet : _bullets) {
      _bullet->copyPlayer(player);
      _bullet->copyEnemyVector(_enemies);
      _bullet->copyFixedEnemyVector(_fixedEnemies);
    }

    for (auto _bomb : _bombs) {
      _bomb->copyPlayer(player);
      _bomb->copyEnemyVector(_enemies);
      _bomb->copyFixedEnemyVector(_fixedEnemies);
    }

    // Update player information 
    Update();

    // Rendering to screen 
    try {
      renderer.Render(player, _enemies, _bullets, _bombs, _fixedEnemies);
    } catch (std::exception& e) {
      // Block of code to handle errors
      std::cerr << "rendering fail: " << e.what() << std::endl;
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
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


void Game::Update() {
  if (!player->isAlive()) {
    return;
  }

  player->Update();

  int pos_x, pos_y; 
  player->getPosition(pos_x, pos_y);

  int new_x = static_cast<int>(pos_x);
  int new_y = static_cast<int>(pos_y);
}


int Game::GetScore() const { return score; }
int Game::GetSize() { return player->getSize(); }