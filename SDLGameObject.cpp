#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : 
GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
    m_textureID = pParams->getTextureID();

    m_width = pParams->getwidth();
    m_height = pParams->getheight();

    m_currentFrame = 1;
    m_currentRow = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::clean()
{

}