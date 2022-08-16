#include "GameOverState.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::update() 
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        if(TheGame::Instance()->getStateMachine()->getNewState()) {
            TheGame::Instance()->getStateMachine()->changeState();
            return;
        }
        m_gameObjects[i]->update();
    }
}

void GameOverState::render()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
}
    
bool GameOverState::onEnter()
{
    if(!TheTextureManager::Instance()->load("resources/src/gameover.png", "gameovertext", TheGame::Instance()->getRenderer())) {
        printf("Error load resources GameOverState::onEnter\n");
        return false;
    }
    if(!TheTextureManager::Instance()->load("resources/src/main.png", "mainbutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources GameOverState::onEnter\n");
        return false;
    }
    if(!TheTextureManager::Instance()->load("resources/src/restart.png", "restartbutton", TheGame::Instance()->getRenderer())) {
        printf("Error load resources GameOverState::onEnter\n");
        return false;
    }
    GameObject *gameOverText = new AnimatedGraphic(new LoaderParams(200, 100, 190, 30, "gameovertext", 2), 2);
    GameObject *button1 = new MenuButton(new LoaderParams(200, 200, 200, 80, "mainbutton"), s_gameOverToMain);
    GameObject *button2 = new MenuButton(new LoaderParams(200, 300, 200, 80, "restartbutton"), s_restartPlay);

    m_gameObjects.push_back(gameOverText);
    m_gameObjects.push_back(button1);
    m_gameObjects.push_back(button2);
    
    printf("Entering GameOverState\n");
    return true;
}

bool GameOverState::onExit()
{
    for(int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
    TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
    TheTextureManager::Instance()->clearFromTextureMap("restartbutton");
    printf("Exiting GameOverState onExit\n");
    return true;
}

void GameOverState::s_gameOverToMain()
{
    TheGame::Instance()->getStateMachine()->changeState(new MenuState());
    printf("Exiting GameOverState s_pauseToMain\n");
}
void GameOverState::s_restartPlay()
{
    TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}