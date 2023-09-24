#include "renderer.h"
#include <iostream>
#include <string>


void Renderer::DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}


void Renderer::DrawText(SDL_Renderer * renderer, std::string text, int32_t x, int32_t y, SDL_Color textColor)
{
  SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
  SDL_Texture* sdlText = SDL_CreateTextureFromSurface(renderer, textSurface);
  int text_width = textSurface->w;
  int text_height = textSurface->h;
  SDL_FreeSurface(textSurface);
  
  int win_height = 640;
  SDL_Rect renderQuad = { static_cast<int>(x), static_cast<int>(y), text_width, text_height };
  SDL_RenderCopy(renderer, sdlText, NULL, &renderQuad);
  SDL_DestroyTexture(sdlText);
}


Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (TTF_Init() != 0) {
    std::cerr << "failed to init the TTF: " << TTF_GetError() << std::endl;
  }

  font = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 18);
  if(!font) {
    std::cerr << "no font found: " << TTF_GetError() << std::endl;
  }
}


Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(Player player, SDL_Point const &food, std::shared_ptr<Enemy> enemy,
                      std::vector<std::shared_ptr<Bullet>> bullets) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

  // Render player
  int player_pos_x, player_pos_y; 
  player.getPosition(player_pos_x, player_pos_y);

  int player_hp;
  player.getHp(player_hp);
  std::string hp_text = std::to_string(player_hp);
  SDL_Color textColor = { 255, 255, 255, 0 };
  //DrawText(sdl_renderer, score_text, player_pos_x, player_pos_y - 1.5, textColor);
  DrawText(sdl_renderer, "player", player_pos_x, player_pos_y, textColor);

  if (player.isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    //DrawCircle(sdl_renderer, 
    //           static_cast<int>(player_pos_x) * block.w + int(block.w / 2), 
    //           static_cast<int>(player_pos_y) * block.h + int(block.h / 2), 20);
    DrawCircle(sdl_renderer, player_pos_x, player_pos_y, 5 * player.getSize());
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

  // Render Enemy
  int enemy_pos_x, enemy_pos_y; 
  enemy->getPosition(enemy_pos_x, enemy_pos_y);

  int enemy_hp;
  enemy->getHp(enemy_hp);
  hp_text = std::to_string(enemy_hp);
  textColor = { 255, 0, 0, 0 };
  DrawText(sdl_renderer, "enemy", enemy_pos_x, enemy_pos_y, textColor);
  DrawText(sdl_renderer, hp_text, enemy_pos_x, enemy_pos_y - 25, textColor);

  if (enemy->isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
    DrawCircle(sdl_renderer, 
               static_cast<int>(enemy_pos_x), static_cast<int>(enemy_pos_y), 5 * enemy->getSize());
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

  // Render Bullets
  for (auto bullet : bullets)
  {
    int bullet_pos_x, bullet_pos_y; 
    bullet->getPosition(bullet_pos_x, bullet_pos_y);

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
    DrawCircle(sdl_renderer, 
               static_cast<int>(bullet_pos_x), static_cast<int>(bullet_pos_y), 5 * bullet->getSize());
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Player Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
