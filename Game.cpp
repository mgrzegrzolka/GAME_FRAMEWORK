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

    
    //m_go.load(100, 100, 128, 82, "animate");
    //m_player.load(300, 300, 128, 82, "animate");
    //Texture render 1
    /*
    SDL_Surface *pTempSurface = SDL_LoadBMP("resources/src/rider.bmp");
    m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    */
    //Texture render

    //Sprite render
    /*
    SDL_Surface *pTempSurface = IMG_Load("resources/src/animate-alpha.png");
    m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    m_sourceRectangle.w = 128;
    m_sourceRectangle.h = 82;
    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;
    */
    //Sprite render

    return true;
}

void Game::render()
{
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 255, 255);
    SDL_RenderClear(g_pRenderer);
    //SDL_RenderCopyEx(g_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_NONE/*SDL_FLIP_HORIZONTAL*/);
    
    //TheTextureManager::Instance()->draw("animate", 0,0, 128, 82, g_pRenderer);
    //TheTextureManager::Instance()->drawFrame("animate", 100,100, 128, 82, 1, m_currentFrame, g_pRenderer);;
    //m_go.draw(g_pRenderer);
    //m_player.draw(g_pRenderer);
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
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
}

void Game::update()
{
    //m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }
}

void Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                printf("Info: handleEvents() SDL_QUIT quit game\n");
                m_bRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_q:
                        printf("Info: handleEvents() SDLK_Q quit game\n");
                        m_bRunning = false;
                        break;
                    default:
                        break;
                }
            default:
                break;
        }
    }
}