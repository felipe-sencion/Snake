#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
using namespace std;

class Game
{
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int screenWidth;
    int screenHeight;

public:
    Game();
    bool getIsRunning() const;
    void setIsRunning(bool value);
    SDL_Window *getWindow() const;
    void setWindow(SDL_Window *value);
    SDL_Renderer *getRenderer() const;
    void setRenderer(SDL_Renderer *value);
    int getScreenWidth() const;
    void setScreenWidth(int value);
    int getScreenHeight() const;
    void setScreenHeight(int value);

    //init("título", ancho, alto, ¿pantallaCompleta?)
    void init(const char *title, int w, int h, bool fullscreen);
    virtual void run() = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
};

#endif // GAME_H
