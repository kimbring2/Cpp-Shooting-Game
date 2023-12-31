#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "bomb.h"
#include "fixedEnemy.h"
#include "boss.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(std::shared_ptr<Player>, std::vector<std::shared_ptr<Enemy>>, 
              std::vector<std::shared_ptr<Bullet>>, std::vector<std::shared_ptr<Bomb>>,
              std::vector<std::shared_ptr<FixedEnemy>>, std::vector<std::shared_ptr<Boss>>);
  void UpdateWindowTitle(int score, int fps);

  void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
  void DrawText(SDL_Renderer * renderer, std::string text, int32_t x, int32_t y, SDL_Color textColor,
                TTF_Font *font);
  void DrawProgressBar(SDL_Renderer * renderer, int32_t progress, int32_t x, int32_t y);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  TTF_Font *font_18;
  TTF_Font *font_30;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif