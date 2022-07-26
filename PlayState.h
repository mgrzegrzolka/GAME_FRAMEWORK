#ifndef __PlayState__
#define __PlayState__
#include <string>
#include <vector>
#include "GameState.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"


class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID;};
    virtual bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);
private:
    static const std::string s_playID;
    std::vector<GameObject*> m_gameObjects;
};

#endif /* defined(__PlayState__) */