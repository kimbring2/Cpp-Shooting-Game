#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "enemy.h"
#include "bullet.h"


class Controller {
 public:
  void HandleInput(bool &running, Player &player);

  bool _bulletSpawned = false;
  int _bullet_x, _bullet_y;
  bool _bullet_mine;

  //Bullet _bullet;

 private:
  void ChangeDirection(Player &player, Player::Direction input,
                       Player::Direction opposite) const;
};

#endif