#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams *pParams) : SDLGameObject(pParams)
{

}

void Player::draw()
{
    SDLGameObject::draw();
}

void Player::update()
{
    m_velocity.setX(0);
    m_velocity.setY(0);

    handleInput();
    
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    //m_acceleration.setX(1);
    //m_position.setX(m_position.getX() - 1);
    SDLGameObject::update();
}

void Player::clean()
{

}

void Player::handleInput()
{
    int vValue;
    if(TheInputHandler::Instance()->joysticksInitialised()) {
        vValue = TheInputHandler::Instance()->xvalue(0, 1); /* joy nr 0 - left stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setX((float)vValue);
        }
        vValue = TheInputHandler::Instance()->yvalue(0, 1); /*  joy nr 0 -  left stick y */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setY((float)vValue);
        }
        vValue = TheInputHandler::Instance()->xvalue(0, 2); /*  joy nr 0 -  right stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setX((float)vValue);
        }
        vValue = TheInputHandler::Instance()->yvalue(0, 2); /*  joy nr 0 -  right stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setY((float)vValue);
        }
    }
}