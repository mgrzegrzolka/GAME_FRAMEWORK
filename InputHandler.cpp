#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::s_pInstance = 0;

InputHandler::InputHandler() : m_mousePosition(new Vector2D(0, 0)), m_keystate(SDL_GetKeyboardState(0))
{
    for(int i = 0; i <= RIGHT; i++) { /* mouse buttons 0-left 1-middle 2-right. On start default false */ 
        m_mouseButtonStates.push_back(false);
    }
}

void InputHandler::update()
{
    SDL_Event event;
    int whichOne;

    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            printf("Info: handleEvents() SDL_QUIT quit game\n");
            TheGame::Instance()->quit();
            break;
        
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_q:
                    printf("Info: handleEvents() SDLK_Q quit game\n");
                    TheGame::Instance()->quit();
                    break;
                default:
                    break;
            }
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        default:
                break;
        }
    }
}

void InputHandler::clean()
{
    if(m_bJoysticksInitialised) {
        for(int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::initialiseJoysticks()
{
   std::vector<bool> tempButtons;
   
   if(SDL_WasInit(SDL_INIT_JOYSTICK)) {
       SDL_InitSubSystem(SDL_INIT_JOYSTICK);
   }

   if(SDL_NumJoysticks() > 0) {
       for(int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_Joystick *joy = SDL_JoystickOpen(i);

            if(joy) {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); /* two axes of motion for each sticks - two sticks pair(1 - stick, 2 - stick) */

                for(int j = 0; j < SDL_JoystickNumButtons(joy); j++ ) {
                    tempButtons.push_back(false);
                }

                m_buttonStates.push_back(tempButtons);
                tempButtons.clear();
            } else {
                printf("%s", SDL_GetError());
            }
       }
       SDL_JoystickEventState(SDL_ENABLE);
       m_bJoysticksInitialised = true;

       printf("Initialised %d joystick(s)", m_joysticks.size());
   } else {
       m_bJoysticksInitialised = false;
   }
}

int InputHandler::xvalue(int joy, int stick)
{
    if(m_joystickValues.size() > 0) {
        if(stick == 1) {
            return m_joystickValues[joy].first->getX();
        } else if(stick == 2) {
            return m_joystickValues[joy].second->getX();
        }
    }
    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if(m_joystickValues.size() > 0) {
        if(stick == 1) {
            return m_joystickValues[joy].first->getY();
        } else if(stick == 2) {
            return m_joystickValues[joy].second->getY();
        }
    }
    return 0;
} 

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if(m_keystate != 0) {
        if(m_keystate[key] == 1) {
            return true;
        } else {
            return false;
        }
    } 
    return false;
}

void InputHandler::onKeyDown()
{

}

void InputHandler::onKeyUp()
{

}

void InputHandler::onMouseMove(SDL_Event &event)
{
    m_mousePosition->setX(event.motion.x);
    m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event &event)
{
    if(event.button.button = SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = true;
    }
    if(event.button.button = SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = true;
    }
    if(event.button.button = SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::onMouseButtonUp(SDL_Event &event)
{
    if(event.button.button = SDL_BUTTON_LEFT) {
        m_mouseButtonStates[LEFT] = false;
    }
    if(event.button.button = SDL_BUTTON_MIDDLE) {
        m_mouseButtonStates[MIDDLE] = false;
    }
    if(event.button.button = SDL_BUTTON_RIGHT) {
        m_mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    /* https://wiki.libsdl.org/SDL_GameControllerAxis */
    /* FIST  STICK */
    if(event.jaxis.axis == 0) { /* SDL_CONTROLLER_AXIS_LEFTX L R*/
        if(event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(-1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setX(1);
        } else {
            m_joystickValues[whichOne].first->setX(0);
        }
    }
    if(event.jaxis.axis == 1) { /* SDL_CONTROLLER_AXIS_LEFTY U D*/
        if(event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(-1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].first->setY(1);
        } else {
            m_joystickValues[whichOne].first->setY(0);
        }
    }
    /* SECOND  STICK */
    if(event.jaxis.axis == 2) { /* SDL_CONTROLLER_AXIS_RIGHTX L R*/
        if(event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(-1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setX(1);
        } else {
            m_joystickValues[whichOne].second->setX(0);
        }
    }
    if(event.jaxis.axis == 3) { /* SDL_CONTROLLER_AXIS_RIGHTY U D*/
        if(event.jaxis.value > m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(-1);
        } else if(event.jaxis.value < -m_joystickDeadZone) {
            m_joystickValues[whichOne].second->setY(1);
        } else {
            m_joystickValues[whichOne].second->setY(0);
        }
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event &event)
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event &event) 
{
    int whichOne = event.jaxis.which;
    m_buttonStates[whichOne][event.jbutton.button] = false;
}
