#include "game.h"

bool Game::getIsRunning() const
{
    return isRunning;
}

void Game::setIsRunning(bool value)
{
    isRunning = value;
}

SDL_Window *Game::getWindow() const
{
    return window;
}

void Game::setWindow(SDL_Window *value)
{
    window = value;
}

SDL_Renderer *Game::getRenderer() const
{
    return renderer;
}

void Game::setRenderer(SDL_Renderer *value)
{
    renderer = value;
}

int Game::getScreenWidth() const
{
    return screenWidth;
}

void Game::setScreenWidth(int value)
{
    screenWidth = value;
}

int Game::getScreenHeight() const
{
    return screenHeight;
}

void Game::setScreenHeight(int value)
{
    screenHeight = value;
}

Game::Game()
{
    isRunning = false;
}

void Game::init(const char *title, int w, int h, bool fullscreen)
{
    int flags = 0;
    screenWidth = w;
    screenHeight = h;

    if (fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        //SDL_CreateWindow(titulo, posX, posY, ancho, alto, banderas)
        window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  screenWidth,
                                  screenHeight,
                                  flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            //SDL_SetRenderDrawColor(renderer, r, g, b, alpha)
            // r, g  y b son valores entre 0 y 255
            // 0, 0, 0 es color negro
            // 255, 255, 255, es color blanco
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        else
            cout <<"couldn't initialize renderer " <<SDL_GetError() <<endl;

        isRunning = true;
    }
}
