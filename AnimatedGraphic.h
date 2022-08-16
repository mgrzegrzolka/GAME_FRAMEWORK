#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__
#include "SDLGameObject.h"


class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic(const LoaderParams* pParams, int animspeed);

    void draw();
    void update();
    void clean();
private:
    int m_animSpeed;
};

#endif /* defined(__AnimatedGraphic__) */