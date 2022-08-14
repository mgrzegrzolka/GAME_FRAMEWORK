#ifndef __GameStateMachine__
#define __GameStateMachine__
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    void pushState(GameState *pState);
    void changeState(GameState *pState);
    void popState();

    void update();
    void render();
    
    bool getNewState() { return newState; }
    void changeState() { newState = false; }
private:
    std::vector<GameState*> m_gameStates;
    bool newState;
};

#endif /* defined(__GameStateMachine__) */