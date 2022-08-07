#ifndef __PlayState__
#define __PlayState__
#include <string>
#include "GameState.h"

class PlayState : public GameState
{
public:
    virtual void update();
    virtual void render();
    
    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_playID;};
private:
    static const std::string s_playID;
};

#endif /* defined(__PlayState__) */