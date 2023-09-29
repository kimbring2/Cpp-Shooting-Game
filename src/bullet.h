#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include <thread>
#include <mutex>

#include "gameObject.h"
#include "player.h"
#include "enemy.h"
#include "fixedEnemy.h"
//#include "boss.h"

class Player;
class Enemy;
class FixedEnemy;
class Boss;

class Bullet : public GameObject {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Bullet(float speed, std::size_t screen_width, std::size_t screen_height, 
         std::size_t init_x, std::size_t init_y, std::size_t size, bool mine,
         Direction direction);
  ~Bullet();

  bool getMine() { return _mine; }
  bool getDestroyed() { return _destroyed; }
  void toggleDestroyed() { _destroyed = !_destroyed; }

  void simulate();

  void copyEnemyVector(const std::vector<std::shared_ptr<Enemy>>& sourceVector);
  void copyFixedEnemyVector(const std::vector<std::shared_ptr<FixedEnemy>>& sourceVector);
  void copyBossVector(const std::vector<std::shared_ptr<Boss>>& sourceVector);
  void copyPlayer(const std::shared_ptr<Player>& source);
  double distanceBetweenTwoPoints(int x, int y, int a, int b);

 protected:
  float _speed;
  bool _destroyed = false;
  Direction _direction = Direction::kUp;
  bool _mine;
  std::thread t;
  static std::mutex _mtx;           // mutex shared by all traffic objects for protecting cout 

 private:
  void cycleThroughPhases();
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Enemy>> _enemies;
  std::vector<std::shared_ptr<FixedEnemy>> _fixedEnemies;
  std::vector<std::shared_ptr<Boss>> _bosses;
};

#endif