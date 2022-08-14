#include "MenuState.h"

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() 
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(TheGame::Instance()->getStateMachine()->getNewState()) {
            TheGame::Instance()->getStateMachine()->changeState();
            return;
        }
        m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
    
bool MenuState::onEnter()
{
    if(!TheTextureManager::Instance()->load("resources/src/button.png", "playbutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources MenuState::onEnter\n");
        return false;
    }
    if(!TheTextureManager::Instance()->load("resources/src/exit.png", "exitbutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources MenuState::onEnter\n");
        return false;
    }
    GameObject *button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), s_menuToPlay);
    GameObject *button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), s_exitFromMenu);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    printf("Entering MenuState\n");
    return true;
}

bool MenuState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("playbutton");
    TheTextureManager::Instance()->clearFromTextureMap("exitbutton");
    printf("Exiting MenuState\n");
    return true;
}

void MenuState::s_menuToPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
    printf("Play button clicked\n");
}
void MenuState::s_exitFromMenu()
{
    TheGame::Instance()->quit();
}