#include "MenuButton.h"

MenuButton::MenuButton(const LoaderParams* pParams, void (*callback)()) : SDLGameObject(pParams), m_callback(callback)
{
    m_currentFrame = MOUSE_OUT;
    
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D *pMousePos = TheInputHandler::Instance()->get_mousePosition();
    bool leftButtonState = TheInputHandler::Instance()->getMouseButtonState(LEFT);
    if(pMousePos->getX() < (m_position.getX() + m_width) && pMousePos->getX() > m_position.getX()
    && pMousePos->getY() < (m_position.getY() + m_height) && pMousePos->getY() > m_position.getY()) {
        if((leftButtonState) && (m_currentFrame == MOUSE_CLICKED) && (!m_bReleased)) return; //you have to release the mouse button for the next event to take effect
        if ((leftButtonState) && (m_currentFrame == MOUSE_OUT)) return; //eliminates instant clicks right after state changes
        m_currentFrame =  MOUSE_OVER;
        if(leftButtonState && m_bReleased) {
            m_currentFrame = MOUSE_CLICKED;
            m_bReleased = false;
            m_callback();
        } else if(leftButtonState) {
            m_bReleased = true;
            m_currentFrame =  MOUSE_OVER;
        }
        
        
    } else {
        m_currentFrame = MOUSE_OUT;
    }
}

void MenuButton::clean()
{
    SDLGameObject::clean();
}