#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Game.h"
#include "resources/ResourceManager.h"

int main(int argc, char* argv[])
{
    std::string path = "../../data/resources.json";
    auto &rm = ResourceManager::getInstance();

    Game& game = Game::getInstance();
    game.init();
    rm.loadAll(game.getRenderer(), path);
    game.run();
    return 0;
}