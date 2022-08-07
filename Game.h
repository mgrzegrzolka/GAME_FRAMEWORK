#ifndef __Game__
#define __Game__

#include <vector>
#include "TextureManager.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

class Game
{
public:
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
    bool init(const char* title, int xpos, int ypos, int height, int width, int flags);
    void render();
    void draw();
    void update();
    void handleEvents();
    void clean();
    bool running() { return m_bRunning; }
    SDL_Renderer* getRenderer() const { return g_pRenderer;}
    void quit();
private:
    Game() {}
    ~Game() {}
    static Game *s_pInstance;

    bool m_bRunning = false;

    SDL_Window *g_pWindow = 0;
    SDL_Renderer *g_pRenderer = 0;

    SDL_Texture *m_pTexture;
    //SDL_Rect m_sourceRectangle;
    //SDL_Rect m_destinationRectangle;
    //int m_currentFrame;
    //TextureManager m_textureManager;

    GameObject *m_go;
    GameObject *m_player;
    GameObject *m_enemy;

    std::vector<GameObject*> m_gameObjects;
    GameStateMachine *m_pGameStateMachine;
};

typedef Game TheGame;
#endif /* defined(__Game__) */