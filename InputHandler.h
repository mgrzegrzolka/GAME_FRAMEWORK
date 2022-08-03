#ifndef __InputHandler__
#define __InputHandler__
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

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
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);
    bool getButtonState(int joy, int buttonNumber) {
        return m_buttonStates[joy][buttonNumber]; /* id_joy, id_button */
    }

private:
    InputHandler() {}
    ~InputHandler() {}
    static InputHandler *s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    bool m_bJoysticksInitialised;
    const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;
#endif /* defined(__InputHandler__) */