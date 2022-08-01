#include "Game.h"

Game *Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int height, int width, int flags) 
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    g_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(!g_pWindow){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!g_pRenderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return false;
    }
    printf("Info: init() success\n");
    m_bRunning = true;
    
    TheInputHandler::Instance()->initialiseJoysticks();
    TheTextureManager::Instance()->load("resources/src/animate-alpha.png", "animate", g_pRenderer);
    
    //m_go = new GameObject();
    //m_player = new Player();
    //m_enemy = new Enemy();
    //m_go->load(100, 100, 128, 82, "animate");
    //m_player->load(300, 300, 128, 82, "animate");
    //m_enemy->load(0, 0, 128, 82, "animate");
    //m_gameObjects.push_back(m_go);
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(300, 300, 128, 82, "animate")));

    return true;
}

void Game::render()
{
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255);
    SDL_RenderClear(g_pRenderer);
   
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }

    SDL_RenderPresent(g_pRenderer);
}

void Game::draw()
{
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}

void Game::clean()
{
    printf("Info: clean() clean game\n");
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
}

void Game::update()
{
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::quit()
{
    m_bRunning = false;
}