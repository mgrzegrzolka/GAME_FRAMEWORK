cmake_minimum_required (VERSION 2.8.11)

project(GAME_FRAMEWORK)

if(WIN32)
    include_directories("$ENV{VCPKG_PATH}\\include")
    link_directories("$ENV{VCPKG_PATH}\\lib")
    ADD_DEFINITIONS(-DNODEFAULTLIB:msvcrt.lib)
endif(WIN32)

if(WIN32)
else(WIN32)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(WIN32)

include_directories(externals)

#common part od source code 
set(game_framework_src
        main.cpp
        Game.h
        Game.cpp
        TextureManager.h
        TextureManager.cpp
        GameObject.h
        SDLGameObject.h
        SDLGameObject.cpp
        Player.h
        Player.cpp
        Enemy.h
        Enemy.cpp
        LoaderParams.h
        Vector2D.h
        InputHandler.h
        InputHandler.cpp
        GameState.h
        MenuState.h
        MenuState.cpp
        PlayState.h
        PlayState.cpp
        GameStateMachine.h
        GameStateMachine.cpp
        MenuButton.h
        MenuButton.cpp
        PauseState.h
        PauseState.cpp
        AnimatedGraphic.h
        AnimatedGraphic.cpp
        GameOverState.h
        GameOverState.cpp
        GameObjectFactory.h
        GameObjectFactory.cpp

)

add_executable(${PROJECT_NAME} ${game_framework_src})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx)
else()
    target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_ttf SDL2_mixer SDL2_image SDL2_gfx)
endif()

