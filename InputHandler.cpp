#include "InputHandler.h"
#include "Game.h"

InputHandler *InputHandler::s_pInstance = 0;

void InputHandler::update()
{
    SDL_Event event;

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