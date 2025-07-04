#include "SceneMain.h"
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>



SceneMain::SceneMain() : game(Game::getInstance())
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::update()
{
}

void SceneMain::render()
{
    SDL_Rect playerRect{
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        player.width,
        player.height
    };
    SDL_RenderCopy(game.getRenderer(), player.texture, NULL, &playerRect);
}

void SceneMain::handleEvent(SDL_Event *event)
{
}

void SceneMain::init()
{
    player.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/SpaceShip.png");
    SDL_QueryTexture(player.texture, NULL, NULL, &player.width, &player.height);
    player.position.x = static_cast<float>(game.getWindowWidth()) / 2 - static_cast<float>(player.width) / 2;
    player.position.y = static_cast<float>(game.getWindowHeight()) - static_cast<float>(player.height);
}

void SceneMain::clean()
{
    if (player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
    }
}
