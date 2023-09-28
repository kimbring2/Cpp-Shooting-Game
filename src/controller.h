#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "bomb.h"


class Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Player> player);

  bool _bullet_spawned = false;
  bool _bomb_spawned = false;

  int _bullet_x, _bullet_y;
  bool _bullet_mine;
  int _bullet_timer = 0;
  Bullet::Direction _bullet_direction;

  int _bomb_x, _bomb_y;
  bool _bomb_mine;
  Bomb::Direction _bomb_direction;

 private:
  void ChangeDirection(std::shared_ptr<Player> player, Player::Direction input,
                       Player::Direction opposite) const;
};

#endif