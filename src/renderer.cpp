#include "renderer.h"
#include <iostream>
#include <string>


void Renderer::DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, 
                          int32_t radius) {
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y) {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0){
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0) {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}


void Renderer::DrawText(SDL_Renderer * renderer, std::string text, int32_t x, int32_t y, 
                        SDL_Color textColor, TTF_Font *font) {
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


void Renderer::DrawProgressBar(SDL_Renderer *renderer, int32_t progress, int32_t x, int32_t y) {
  // Progress bar
  SDL_Rect progressBar;  // Rectangle for the progress bar
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  progressBar.x = x;           // X position
  progressBar.y = y;           // Y position
  progressBar.w = progress * 2;  // Width based on progress (assuming a total of 100 units)
  progressBar.h = 30;            // Height

  // Draw the filled part of the progress bar
  SDL_RenderFillRect(renderer, &progressBar);

  // Set a different color for the unfilled part
  SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Gray for unfilled part

  // Draw the unfilled part of the progress bar
  SDL_Rect unfilledBar = { progressBar.x + progressBar.w, progressBar.y, (100 - progress) * 2, progressBar.h };
  SDL_RenderFillRect(renderer, &unfilledBar);
}


Renderer::Renderer(const std::size_t screen_width, const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                screen_width, screen_height + screen_height / 4, SDL_WINDOW_SHOWN);

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

  font_18 = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 18);
  font_30 = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeSans.ttf", 30);
}


Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}


void Renderer::Render(std::shared_ptr<Player> player, 
                      std::vector<std::shared_ptr<Enemy>> enemies,
                      std::vector<std::shared_ptr<Bullet>> bullets,
                      std::vector<std::shared_ptr<Bomb>> bombs,
                      std::vector<std::shared_ptr<FixedEnemy>> fixedEnemies,
                      std::vector<std::shared_ptr<Boss>> bosses) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  SDL_Color textColor = { 255, 255, 255, 0 }; // White color

  // Render player
  int player_pos_x, player_pos_y; 
  player->getPosition(player_pos_x, player_pos_y);
  DrawText(sdl_renderer, "player", player_pos_x, player_pos_y, textColor, font_18);

  if (player->isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    DrawCircle(sdl_renderer, player_pos_x, player_pos_y, 5 * player->getSize());
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }

  // Render Enemies
  for (auto enemy : enemies) {
    int enemy_pos_x, enemy_pos_y; 
    enemy->getPosition(enemy_pos_x, enemy_pos_y);

    int enemy_hp = enemy->getHp();
    std::string hp_text = std::to_string(enemy_hp);
    textColor = { 255, 0, 0, 0 };
    DrawText(sdl_renderer, "enemy", enemy_pos_x, enemy_pos_y, textColor, font_18);
    DrawText(sdl_renderer, hp_text, enemy_pos_x, enemy_pos_y - 25, textColor, font_18);

    if (enemy->isAlive()) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
      DrawCircle(sdl_renderer, 
                 static_cast<int>(enemy_pos_x), static_cast<int>(enemy_pos_y), 5 * enemy->getSize());
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
  }

  // Render Bullets
  for (auto bullet : bullets) {
    int bullet_pos_x, bullet_pos_y; 
    bullet->getPosition(bullet_pos_x, bullet_pos_y);

    if (bullet->getMine()) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
    }
    
    DrawCircle(sdl_renderer, 
               static_cast<int>(bullet_pos_x), static_cast<int>(bullet_pos_y), 5 * bullet->getSize());
  }

  // Render Bomb
  for (auto bomb : bombs) {
    int bomb_pos_x, bomb_pos_y; 
    bomb->getPosition(bomb_pos_x, bomb_pos_y);
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    DrawCircle(sdl_renderer, 
               static_cast<int>(bomb_pos_x), static_cast<int>(bomb_pos_y), 10 * bomb->getSize());
  }

  // Render Fixed Enemies
  for (auto fixedEnemy : fixedEnemies) {
    int fixed_enemy_pos_x, fixed_enemy_pos_y; 
    fixedEnemy->getPosition(fixed_enemy_pos_x, fixed_enemy_pos_y);

    int fixed_enemy_hp = fixedEnemy->getHp();
    std::string fixed_hp_text = std::to_string(fixed_enemy_hp);
    textColor = { 255, 0, 0, 0 };
    DrawText(sdl_renderer, "fixed_enemy", fixed_enemy_pos_x, fixed_enemy_pos_y - 40, textColor, font_18);
    DrawText(sdl_renderer, fixed_hp_text, fixed_enemy_pos_x, fixed_enemy_pos_y + 25, textColor, font_18);

    fixed_enemy_pos_x -= 5 * fixedEnemy->getSize();
    fixed_enemy_pos_y -= 5 * fixedEnemy->getSize();

    if (fixedEnemy->isAlive()) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
      SDL_Rect rect = { static_cast<int>(fixed_enemy_pos_x), static_cast<int>(fixed_enemy_pos_y), 
                        10 * fixedEnemy->getSize(), 10 * fixedEnemy->getSize() };
      SDL_RenderFillRect(sdl_renderer, &rect);
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
  }

  // Render Bosses
  for (auto boss : bosses) {
    int boss_pos_x, boss_pos_y; 
    boss->getPosition(boss_pos_x, boss_pos_y);

    int boss_hp = boss->getHp();
    std::string hp_text = std::to_string(boss_hp);
    textColor = { 255, 0, 0, 0 };
    DrawText(sdl_renderer, "boss", boss_pos_x, boss_pos_y, textColor, font_18);
    DrawText(sdl_renderer, hp_text, boss_pos_x, boss_pos_y - 25, textColor, font_18);

    if (boss->isAlive()) {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0xCC, 0x7A);
      DrawCircle(sdl_renderer, 
                 static_cast<int>(boss_pos_x), static_cast<int>(boss_pos_y), 5 * boss->getSize());
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
  }

  // Draw infomation panel
  //sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
  //                              screen_width, screen_height + screen_height / 4, SDL_WINDOW_SHOWN);
  SDL_Point startPoint = {0, (int) screen_height};
  SDL_Point endPoint = {(int) screen_width, (int) screen_height};
  SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 0); // White color
  SDL_RenderDrawLine(sdl_renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);

  textColor = { 255, 255, 255, 0 }; // White color
  DrawText(sdl_renderer, "HP", 190, screen_height + 50, textColor, font_30);
  int player_hp = player->getHp();
  DrawProgressBar(sdl_renderer, player_hp, 240, screen_height + 50);
  std::string hp_text = std::to_string(player_hp);
  DrawText(sdl_renderer, hp_text, 450, screen_height + 50, textColor, font_30);

  int bomb_count = player->getBombCount();
  std::string bomb_text = "Bomb: " + std::to_string(bomb_count);
  textColor = { 255, 255, 255, 0 }; // White color
  DrawText(sdl_renderer, bomb_text, 0, screen_height + 50, textColor, font_30);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Player Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
