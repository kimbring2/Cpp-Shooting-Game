#include "game.h"
#include <iostream>
#include <exception>
#include <cmath>
#include "SDL.h"


Game::Game(std::size_t screen_width, std::size_t screen_height)
    : player(100, 10, screen_width, screen_height, 300, 590, 5), engine(dev()),
      random_w(0, static_cast<int>(screen_width - 1)), random_h(0, static_cast<int>(screen_height - 1)) {
  PlaceFood();

  _enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 100, 300, 5));
  //_enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 120, 250, 5));
  //_enemies.emplace_back(std::make_shared<Enemy>(100, 10, screen_width, screen_height, 379, 50, 5));
}


Game::~Game() {
  std::cout << "Game Destructor" << std::endl;

  delete &player;

  // delete all enemy
  for (auto it = std::begin(_enemies); it != std::end(_enemies); ++it) {
    (*it)->toggleAlive();
    delete it->get();
  }

  // delete all bullet
  for (auto it = std::begin(_bullets); it != std::end(_bullets); ++it) {
    (*it)->toggleDestroyed();
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

  for (auto enemy : _enemies) {
    enemy->simulate();
  }

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);

    if (controller._bulletSpawned == true) {
      controller._bulletSpawned = false;

      std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(10, 640, 640, 
        controller._bullet_x, controller._bullet_y, 
        1, controller._bullet_mine);

      _bullets.emplace_back(bullet);
      bullet->simulate();
    }

    // Delete the destroyed bullet
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), 
                   [](std::shared_ptr<Bullet> bullet) { 
                    return bullet->getDestroyed();
                   }), _bullets.end());

    _enemies.erase(std::remove_if(_enemies.begin(), _enemies.end(), 
                   [](std::shared_ptr<Enemy> enemy) { 
                    return !enemy->isAlive();
                   }), _enemies.end());

    // 
    for (auto _bullet : _bullets) {
      _bullet->copySharedVector(_enemies);
    }

    /*
    int player_hp;
    player.getHp(player_hp);

    int player_size = player.getSize();

    // Destory bullet when it goes out ouside of screen
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), boundary_to_remove), 
                   _bullets.end());


    // Collision detection loop
    for (auto it_e = _enemies.begin(); it_e != _enemies.end();) {
      int enemy_pos_x, enemy_pos_y; 
      (*it_e)->getPosition(enemy_pos_x, enemy_pos_y);
      int enemy_size = (*it_e)->getSize();

      int enemy_hp;
      (*it_e)->getHp(enemy_hp);

      
      for (auto it_b = _bullets.begin(); it_b != _bullets.end();) {
        int _bullet_pos_x, _bullet_pos_y;
        (*it_b)->getPosition(_bullet_pos_x, _bullet_pos_y);

        float distance = distanceBetweenTwoPoints(enemy_pos_x, enemy_pos_y, 
                                                  _bullet_pos_x, _bullet_pos_y);

        // If distance between the unit and bullet is below sum of size of both 
        float collision_dis_enemy = (*it_b)->getSize() + enemy_size;
        float collision_dis_player = player.getSize() + enemy_size;

        if ( (*it_b)->getMine() ) {
          if (distance <= collision_dis_enemy * 5) {
            // Enemy collision with bullet
            (*it_b)->_destroyed = true;
            it_b = _bullets.erase(it_b);

            if (enemy_hp > 10) {
              (*it_e)->setHp(enemy_hp - 10);
            } else {
              //std::cout << "enemy die" << std::endl;
              (*it_e)->toggleAlive();
            }
          } else {
            it_b++;
          }
        } else {
          if (distance <= collision_dis_player * 5) {
            // Player collision with bullet
            if (player_hp > 10) {
              player.setHp(player_hp - 10);
            } else {
              std::cout << "player die" << std::endl;
            }
          } else {
            it_b++;
          }
        }
      }

      if (!(*it_e)->isAlive()) {
        it_e = _enemies.erase(it_e);
      } else {
        it_e++;
      }
    }
    */

    Update();

    try {
      renderer.Render(player, food, _enemies, _bullets);
    } catch (std::exception& e) {
      // Block of code to handle errors
      std::cerr << "rendering fail" << std::endl;
      std::cerr << e.what() << std::endl;
    }

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
  if (!player.isAlive()) return;

  player.Update();

  int pos_x, pos_y; 
  player.getPosition(pos_x, pos_y);

  int new_x = static_cast<int>(pos_x);
  int new_y = static_cast<int>(pos_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
  }

  //enemy->Update();
  for (auto enemy : _enemies) {
    enemy->Update();
  }
}


int Game::GetScore() const { return score; }
int Game::GetSize() { return player.getSize(); }