#include <SDL2/SDL.h>
#include <stdio.h>
#include "Game.h"

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS; /* delay time in ms */

int main(int argc, char** argv)
{
    Uint32 frameStart, frameTime;    

    if(!TheGame::Instance()->init("Chapter 1", 100, 100, SCREEN_HEIGHT, SCREEN_WIDTH, 0/*SDL_WINDOW_FULLSCREEN*/)) { 
        printf("Error: init() failed");
        return 0;
    }
    printf("Info: game init success!\n");
    while(TheGame::Instance()->running()) {
        frameStart = SDL_GetTicks();

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    TheGame::Instance()->clean();
    //SDL_Quit();
    return 0;
}