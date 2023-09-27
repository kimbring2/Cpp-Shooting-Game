#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "enemy.h"
#include "bullet.h"


class Controller {
 public:
  void HandleInput(bool &running, std::shared_ptr<Player> player);

  bool _bulletSpawned = false;
  bool _bombSpawned = false;

  int _bullet_x, _bullet_y;
  bool _bullet_mine;

  int _bomb_x, _bomb_y;
  bool _bomb_mine;

  //Bullet _bullet;

 private:
  void ChangeDirection(std::shared_ptr<Player> player, Player::Direction input,
                       Player::Direction opposite) const;
};

#endif