#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include "game.h"
#include "snake.h"
#include <SDL2/SDL_mixer.h>

class SnakeGame : public Game
{
private:
    Snake *snake;
    SDL_Rect food;
    Mix_Music *uh;

    void createFood();
    bool frameCollision();
public:
    SnakeGame();

    void run();
    void handleEvents();
    void update();
    void render();
    void clean();
};

#endif // SNAKEGAME_H
