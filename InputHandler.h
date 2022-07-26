#ifndef __InputHandler__
#define __InputHandler__
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

enum mouse_buttons 
{
    LEFT = 0,
    MIDDLE = 1,
    RIGHT = 2
};

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
    bool getMouseButtonState(int buttonNumber) {
        return m_mouseButtonStates[buttonNumber];
    }
    Vector2D* get_mousePosition() {
        return m_mousePosition;
    }
    bool isKeyDown(SDL_Scancode key);

    //handle keboard events
    void onKeyDown();
    void onKeyUp();

    //handle mouse events
    void onMouseMove(SDL_Event &event);
    void onMouseButtonDown(SDL_Event &event);
    void onMouseButtonUp(SDL_Event &event);

    //handle joysticks events
    void onJoystickAxisMove(SDL_Event &event);
    void onJoystickButtonDown(SDL_Event &event);
    void onJoystickButtonUp(SDL_Event &event);

private:
    InputHandler();
    ~InputHandler() {}
    static InputHandler *s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D *m_mousePosition;
    bool m_bJoysticksInitialised;
    const int m_joystickDeadZone = 10000;
    const Uint8 *m_keystate;
};

typedef InputHandler TheInputHandler;
#endif /* defined(__InputHandler__) */