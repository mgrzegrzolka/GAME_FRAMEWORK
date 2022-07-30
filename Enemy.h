#ifndef __Enemy__
#define __Enemy__

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
    public:
        Enemy(const LoaderParams *pParams);
        
        void draw();
        void update();
        void clean();
};

#endif /* defined(__Enemy__) */