#ifndef __GameOverState__
#define __GameOverState__
#include <string>
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "Game.h"
#include "AnimatedGraphic.h"

class GameOverState : public GameState
{
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID;}
private:
    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;

    //call back function
    static void s_gameOverToMain();
    static void s_restartPlay();
};

#endif /* defined(__GameOverState__) */