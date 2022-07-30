#include <SDL2/SDL.h>
#include <stdio.h>
#include "Game.h"

#define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 480

Game *g_game = 0;

int main(int argc, char** argv){
    
    //g_game = new Game();

    if(!TheGame::Instance()->init("Chapter 1", 100, 100, SCREEN_HEIGHT, SCREEN_WIDTH, 0/*SDL_WINDOW_FULLSCREEN*/)){ 
        printf("Error: init() failed");
        return 0;
    }
    printf("Info: game init success!");
    while(TheGame::Instance()->running()){

        TheGame::Instance()->handleEvents();
        TheGame::Instance()->update();
        TheGame::Instance()->render();

        SDL_Delay(10);
    }

    TheGame::Instance()->clean();
    //SDL_Quit();
    return 0;
}