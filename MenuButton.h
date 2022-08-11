#ifndef __MenuButton__
#define __MenuButton__
#include "SDLGameObject.h"
#include "InputHandler.h"

class MenuButton : public SDLGameObject
{
public:
    MenuButton(const LoaderParams* pParams, void (*m_callback)());

    void draw();
    void update();
    void clean();
private:
    enum button_state {
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        MOUSE_CLICKED = 2
    };
    void (*m_callback)();
    bool m_bReleased;
};

#endif /* defined(__MenuButton__) */