#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::s_pInstance = 0;

InputHandler::InputHandler() {
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
            break;
        case SDL_JOYAXISMOTION:
            whichOne = event.jaxis.which;
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
            break;
        case SDL_JOYBUTTONDOWN:
            whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
            break;
        case SDL_JOYBUTTONUP:
            whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button = SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = true;
            }
            if(event.button.button = SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = true;
            }
            if(event.button.button = SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button = SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = false;
            }
            if(event.button.button = SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = false;
            }
            if(event.button.button = SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = false;
            }
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