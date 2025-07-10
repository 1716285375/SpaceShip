#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Engine.h"
#include "Logger.h"

int main(int argc, char* argv[])
{
    // initLogger();
    // initAsyncLogger();
    Engine& engine = Engine::getInstance();
    engine.run();
    return 0;
}