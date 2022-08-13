#ifndef __PauseState__
#define __PauseState__
#include <string>
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "Game.h"

class PauseState : public GameState
{
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_pauseID;}
private:
    static const std::string s_pauseID;
    std::vector<GameObject*> m_gameObjects;

    //call back function
    static void s_pauseToMain();
    static void s_resumePlay();
};

#endif /* defined(__PauseState__) */