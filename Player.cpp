#include "Player.h"
#include "InputHandler.h"
#include "Vector2D.h"

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
    
    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
    
    //m_acceleration.setX(1);
    //m_position.setX(m_position.getX() - 1);
    SDLGameObject::update();
}

void Player::clean()
{
    SDLGameObject::clean();
}

void Player::handleInput()
{
    Vector2D *target = TheInputHandler::Instance()->get_mousePosition();

    m_velocity = *target - m_position;
    m_velocity /= 50;
    
    //int vValue;
    
    /* MOUSE EVENTS */
    //Vector2D *vec;
    //vec = TheInputHandler::Instance()->get_mousePosition();
    //if(vec) {
    //    m_velocity = (*vec - m_position) / 100;
    //}
    //vValue = TheInputHandler::Instance()->getMouseButtonState(LEFT); /* mouse left button */
    //if(vValue) {
    //    m_velocity.setX(1);
    //}
    
    //if(TheInputHandler::Instance()->joysticksInitialised()) {
    //    vValue = TheInputHandler::Instance()->xvalue(0, 1); /* joy nr 1(2nd) - left stick x */
    //    if((vValue > 0) || (vValue < 0)) {
    //        m_velocity.setX((float)vValue);
    //    }
    //    vValue = TheInputHandler::Instance()->yvalue(0, 1); /*  joy nr 1(2nd) -  left stick y */
    //    if((vValue > 0) || (vValue < 0)) {
    //        m_velocity.setY((float)vValue);
    //    }
    //    vValue = TheInputHandler::Instance()->xvalue(0, 2); /*  joy nr 1(2nd) -  right stick x */
    //    if((vValue > 0) || (vValue < 0)) {
    //        m_velocity.setX((float)vValue);
    //    }
    //    vValue = TheInputHandler::Instance()->yvalue(0, 2); /*  joy nr 1(2nd) -  right stick x */
    //    if((vValue > 0) || (vValue < 0)) {
    //        m_velocity.setY((float)vValue);
    //    }
    //    vValue = TheInputHandler::Instance()->getButtonState(0, 3); /* joy nr 1(2nd) button nr 3(4th) */
    //    if(vValue) {
    //        m_velocity.setX(1);
    //    }
    //}
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)) {
    //    m_velocity.setX(2);
    //}
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)) {
    //    m_velocity.setX(-2);
    //}
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)) {
    //    m_velocity.setY(-2);
    //}
    //if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)) {
    //    m_velocity.setY(2);
    //}
}