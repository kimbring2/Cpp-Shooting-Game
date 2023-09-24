#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Player const Player, SDL_Point const &food, std::shared_ptr<Enemy>, 
              std::vector<std::shared_ptr<Bullet>>);
  void UpdateWindowTitle(int score, int fps);

  void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
  void DrawText(SDL_Renderer * renderer, std::string text, int32_t x, int32_t y, SDL_Color textColor);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  TTF_Font *font;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif