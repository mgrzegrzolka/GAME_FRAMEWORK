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
    if(checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1]))) {
        TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
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
    if(!TheTextureManager::Instance()->load("resources/src/helicopter2.png", "helicopter2", TheGame::Instance()->getRenderer())) {
        printf("Error load resources PlayState::onEnter\n");
        return false;
    }
    GameObject *player = new Player(new LoaderParams(500, 100, 128, 55, "helicopter"));
    GameObject *enemy = new Enemy(new LoaderParams(100, 100, 128, 55, "helicopter2"));
    
    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);
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

bool PlayState::checkCollision(SDLGameObject *p1, SDLGameObject *p2)
{
    int leftA, leftB, rightA, rightB;
    int topA, topB, bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = p1->getPosition().getX() + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = p1->getPosition().getY() + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = p2->getPosition().getX() + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = p2->getPosition().getY() + p2->getHeight();

    if(bottomA <= topB) return false;
    if(topA >= bottomB) return false;
    if(rightA <= leftB) return false;
    if(leftA >= rightB) return false;

    return true;
}