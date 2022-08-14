#include "PauseState.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update() 
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(TheGame::Instance()->getStateMachine()->getNewState()) {
            TheGame::Instance()->getStateMachine()->changeState();
            return;
        }
        m_gameObjects[i]->update();
    }
}

void PauseState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
    
bool PauseState::onEnter()
{
    if(!TheTextureManager::Instance()->load("resources/src/resume.png", "resumebutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources PauseState::onEnter\n");
        return false;
    }
    if(!TheTextureManager::Instance()->load("resources/src/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources PauseState::onEnter\n");
        return false;
    }
    GameObject *button1 = new MenuButton(new LoaderParams(200, 100, 200, 80, "mainbutton"), s_pauseToMain);
    GameObject *button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "resumebutton"), s_resumePlay);

    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    printf("Entering PauseState\n");
    return true;
}

bool PauseState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
    TheTextureManager::Instance()->clearFromTextureMap("resumebutton");
    printf("Exiting PauseState onExit\n");
    return true;
}

void PauseState::s_pauseToMain()
{
    TheGame::Instance()->getStateMachine()->popState();
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
    printf("Exiting PauseState s_pauseToMain\n");
}
void PauseState::s_resumePlay()
{
    TheGame::Instance()->getStateMachine()->popState();
}