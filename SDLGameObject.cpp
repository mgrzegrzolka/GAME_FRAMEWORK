#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams)
{
    m_textureID = pParams->getTextureID();

    m_x = pParams->getX();
    m_y = pParams->getY();

    m_width = pParams->getwidth();
    m_height = pParams->getheight();

    m_currentFrame = 1;
    m_currentRow = 1;
}

void SDLGameObject::draw()
{
    TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{

}

void SDLGameObject::clean()
{

}