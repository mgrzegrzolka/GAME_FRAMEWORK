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
    
    protected:
        
        std::string m_textureID;

        int m_currentFrame;
        int m_currentRow;

        //int m_x;
        //int m_y;
        Vector2D m_position;

        int m_width;
        int m_height;
};

#endif /* defined(__SDLGameObject__) */