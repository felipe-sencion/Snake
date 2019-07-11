#ifndef SNAKE_H
#define SNAKE_H
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Snake
{
private:
    SDL_Renderer *renderer;
    vector<SDL_Rect> body;
    int xDir;
    int yDir;

public:
    static const int BLOCK_WIDTH = 10;
    static const int BLOCK_HEIGHT = 10;
    Snake(int x, int y, SDL_Renderer *r);

    void update();
    void draw(); //dibujar
    bool bodyCollision();
    void grow();
    void setDirection(int x, int y);
    SDL_Rect head();
};

#endif // SNAKE_H
