#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
    public:
        Player(const LoaderParams *pParams);
        
        void draw();
        void update();
        void clean();
        void handleInput();
};

#endif /* defined(__Player__) */