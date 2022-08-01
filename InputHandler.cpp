#include "InputHandler.h"
#include "Game.h"
#include "Vector2D.h"

InputHandler *InputHandler::s_pInstance = 0;

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
            case SDL_JOYAXISMOTION:
                whichOne = event.jaxis.which;
                /* https://wiki.libsdl.org/SDL_GameControllerAxis */
                /* FIST  STICK */
                if(event.jaxis.axis == 0) { /* SDL_CONTROLLER_AXIS_LEFTX L R*/
                    if(event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setX(1);
                    } else if(event.jaxis.value < -m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setX(-1);
                    } else {
                        m_joystickValues[whichOne].first->setX(0);
                    }
                }
                if(event.jaxis.axis == 1) { /* SDL_CONTROLLER_AXIS_LEFTY U D*/
                    if(event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setY(1);
                    } else if(event.jaxis.value < -m_joystickDeadZone) {
                        m_joystickValues[whichOne].first->setY(-1);
                    } else {
                        m_joystickValues[whichOne].first->setY(0);
                    }
                }
                /* SECOND  STICK */
                if(event.jaxis.axis == 2) { /* SDL_CONTROLLER_AXIS_RIGHTX L R*/
                    if(event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setX(1);
                    } else if(event.jaxis.value < -m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setX(-1);
                    } else {
                        m_joystickValues[whichOne].second->setX(0);
                    }
                }
                if(event.jaxis.axis == 3) { /* SDL_CONTROLLER_AXIS_RIGHTY U D*/
                    if(event.jaxis.value > m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setY(1);
                    } else if(event.jaxis.value < -m_joystickDeadZone) {
                        m_joystickValues[whichOne].second->setY(-1);
                    } else {
                        m_joystickValues[whichOne].second->setY(0);
                    }
                }

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
   if(SDL_WasInit(SDL_INIT_JOYSTICK)) {
       SDL_InitSubSystem(SDL_INIT_JOYSTICK);
   }

   if(SDL_NumJoysticks() > 0) {
       for(int i = 0; i < SDL_NumJoysticks(); i++) {
           SDL_Joystick *joy = SDL_JoystickOpen(i);

           if(joy) {
               m_joysticks.push_back(joy);
               m_joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0))); /* two axes of motion for each sticks - two sticks pair(1 - stick, 2 - stick) */
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