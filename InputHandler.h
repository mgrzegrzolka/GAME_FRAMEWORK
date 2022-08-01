#ifndef __InputHandler__
#define __InputHandler__
#include <vector>
#include <SDL2/SDL.h>

class InputHandler
{
public:
    static InputHandler* Instance()
        {
            if(s_pInstance == 0)
            {
                s_pInstance = new InputHandler();
                return s_pInstance;
            }
            return s_pInstance;
        }
    
    void update();
    void clean();
    void initialiseJoysticks();
    bool joysticksInitialised() { return m_bJoysticksInitialised; }

private:
    InputHandler() {}
    ~InputHandler() {}
    static InputHandler *s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    bool m_bJoysticksInitialised;
};

typedef InputHandler TheInputHandler;
#endif /* defined(__InputHandler__) */