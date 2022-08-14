#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() 
{
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
        TheGame::Instance()->getStateMachine()->pushState(new PauseState());
    }
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(TheGame::Instance()->getStateMachine()->getNewState()) {
            TheGame::Instance()->getStateMachine()->changeState();
            return;
        }
        m_gameObjects[i]->update();
    }
}

void PlayState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
    
bool PlayState::onEnter()
{
    if(!TheTextureManager::Instance()->load("resources/src/helicopter.png", "helicopter", TheGame::Instance()->getRenderer())) {
        printf("Error load resources PlayState::onEnter\n");
        return false;
    }
    GameObject *player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
    
    m_gameObjects.push_back(player);
    printf("Entering PlayState\n");
    return true;
}

bool PlayState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("helicopter");
    printf("Exiting PlayState\n");
    return true;
}