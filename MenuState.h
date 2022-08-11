#ifndef __MenuState__
#define __MenuState__
#include <string>
#include <vector>
#include "GameState.h"
#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"

class MenuState : public GameState
{
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID;}
private:
    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;

    //call back function for menu
    static void s_menuToPlay();
    static void s_exitFromMenu();
};

#endif /* defined(__MenuState__) */