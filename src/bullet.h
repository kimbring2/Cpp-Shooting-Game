#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include <iostream>
#include "SDL.h"
#include <thread>
#include <mutex>

#include "gameObject.h"



class Bullet : public GameObject, public std::enable_shared_from_this<Bullet> {
 public:
  enum class Direction { kUp, kDown };

  Bullet(float speed, std::size_t screen_width, std::size_t screen_height, 
         std::size_t init_x, std::size_t init_y, std::size_t size, bool mine);
  ~Bullet();

  bool getMine();

  void simulate();

  bool _destroyed = false;

 protected:
  float _speed;
  Direction _direction = Direction::kUp;
  bool _mine;

  std::thread t;

 private:
  void cycleThroughPhases();  
};

#endif