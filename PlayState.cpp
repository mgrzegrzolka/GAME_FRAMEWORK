#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update() 
{

}

void PlayState::render()
{

}
    
bool PlayState::onEnter()
{
    printf("Entering PlayState\n");
    return true;
}

bool PlayState::onExit()
{
    printf("Exiting PlayState\n");
    return true;
}