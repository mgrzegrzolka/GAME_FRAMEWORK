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
        vValue = TheInputHandler::Instance()->xvalue(1, 1); /* joy nr 1(2nd) - left stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setX((float)vValue);
        }
        vValue = TheInputHandler::Instance()->yvalue(1, 1); /*  joy nr 1(2nd) -  left stick y */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setY((float)vValue);
        }
        vValue = TheInputHandler::Instance()->xvalue(1, 2); /*  joy nr 1(2nd) -  right stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setX((float)vValue);
        }
        vValue = TheInputHandler::Instance()->yvalue(1, 2); /*  joy nr 1(2nd) -  right stick x */
        if((vValue > 0) || (vValue < 0)) {
            m_velocity.setY((float)vValue);
        }
        vValue = TheInputHandler::Instance()->getButtonState(1, 3); /* joy nr 1(2nd) button nr 3(4th) */
        if(vValue) {
            m_velocity.setX(1);
        }
        vValue = TheInputHandler::Instance()->getMouseButtonState(LEFT); /* mouse left button */
        if(vValue) {
            m_velocity.setX(1);
        }
    }
}