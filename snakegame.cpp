#include "snakegame.h"
#include <time.h>

SnakeGame::SnakeGame()
{
    srand(time(NULL));
    init("Snake", 640, 480, false);
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        setIsRunning(false);
    }
    uh = Mix_LoadMUS("uh.mp3");

    int x = rand()%(getScreenWidth()/Snake::BLOCK_WIDTH)*Snake::BLOCK_WIDTH;
    int y = rand()%(getScreenHeight()/Snake::BLOCK_HEIGHT)*Snake::BLOCK_HEIGHT;
    snake = new Snake(x, y, getRenderer());

    createFood();
    run();
}

void SnakeGame::run()
{
    const int FPS = 30;
    const int FRAME_DELAY = 1000 / FPS;
    unsigned int frameStart;
    unsigned int frameTime;

    while(getIsRunning())
    {
        //Tomamos el tiempo de inicio del frame
        frameStart = SDL_GetTicks();
        handleEvents();
        update();
        render();
        //Tomamos el tiempo que tardó el frame
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime)
            SDL_Delay(FRAME_DELAY - frameTime);
    }
    clean();
}

void SnakeGame::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        setIsRunning(false);
        break;
    case SDL_KEYDOWN:
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            cout <<"up" <<endl;
            snake->setDirection(0, -1);
            break;
        case SDLK_DOWN:
            cout <<"down" <<endl;
            snake->setDirection(0, 1);
            break;
        case SDLK_LEFT:
            cout <<"left" <<endl;
            snake->setDirection(-1, 0);
            break;
        case SDLK_RIGHT:
            cout <<"right" <<endl;
            snake->setDirection(1, 0);
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
}

void SnakeGame::update()
{
    SDL_Rect head = snake->head();
    if (head.x == food.x && head.y == food.y)
    {
        snake->grow();
        createFood();
    }
    snake->update();
    if (snake->bodyCollision() || frameCollision())
    {
        //Mix_PlayChannel(-1, uh, 0);
        Mix_PlayMusic(uh, 0);
        SDL_Delay(1000);
        setIsRunning(false);
    }
    /*
     * ¿snake comiendo?
     *      crecer
     *      crear comida
     * actualizar posición
     * evaluar colisiones
     *
     *
     */
}

void SnakeGame::render()
{
    //Limpiar el renderer
    SDL_RenderClear(getRenderer());

    SDL_SetRenderDrawColor(getRenderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(getRenderer(), &food);

    snake->draw();
    //Asignamos un color para dibujar
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);

    //Dibujamos con el renderer
    SDL_RenderPresent(getRenderer());
}

void SnakeGame::clean()
{
    SDL_DestroyWindow(getWindow());
    SDL_DestroyRenderer(getRenderer());
    SDL_Quit();
    Mix_FreeMusic(uh);
    Mix_CloseAudio();
    cout <<"Cleaned" <<endl;
}

void SnakeGame::createFood()
{
    int x = rand()%(getScreenWidth()/Snake::BLOCK_WIDTH)*Snake::BLOCK_WIDTH;
    int y = rand()%(getScreenHeight()/Snake::BLOCK_HEIGHT)*Snake::BLOCK_HEIGHT;

    food.x = x;
    food.y = y;
    food.w = Snake::BLOCK_WIDTH;
    food.h = Snake::BLOCK_HEIGHT;
}

bool SnakeGame::frameCollision()
{
    SDL_Rect head = snake->head();

    if (head.x >= getScreenWidth() || head.x < 0 ||
            head.y >= getScreenHeight() || head.y < 0)
        return true;
    return false;
}
