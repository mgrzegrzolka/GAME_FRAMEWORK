#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : public GameObject
{
    public:
        SDLGameObject(const LoaderParams* pParams);
        virtual void draw();
        virtual void update();
        virtual void clean();
        virtual Vector2D& getPosition() { return m_position; }
        virtual int getWidth() { return m_width; }
        virtual int getHeight() { return m_height; }
    protected:
        
        std::string m_textureID;

        int m_currentFrame;
        int m_currentRow;

        //int m_x;
        //int m_y;
        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;

        int m_width;
        int m_height;
        int m_numFrames;
};

#endif /* defined(__SDLGameObject__) */