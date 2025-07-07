#include "SceneTitle.h"
#include "SceneMain.h"

#include "Game.h"


SceneTitle::~SceneTitle()
{
}

void SceneTitle::init()
{
    bgMusic = Mix_LoadMUS("../../assets/music/06_Battle_in_Space_Intro.ogg");
    Mix_PlayMusic(bgMusic, -1);
}

void SceneTitle::update(float deltaTime)
{
    timer += deltaTime;
    if (timer >= 1.0f)
    {
        timer -= 1.0f;
    }
}

void SceneTitle::render()
{
    std::string titleText = "Space Shoot";
    SDL_Color textColor = { 255, 255, 255, 255 };
    game.renderText(titleText, game.getWindowWidth(), game.getWindowHeight() / 8, 72, textColor, FontType::Silver);
    if (timer < 0.5f)
    {
        std::string startText = "Press key Enter to start";
        game.renderText(startText, game.getWindowWidth(), game.getWindowHeight() / 2, 48, textColor, FontType::Silver);
    }
}

void SceneTitle::clean()
{
    
}

void SceneTitle::handleEvent(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.sym == SDLK_RETURN)
        {
            auto scene = new SceneMain();
            game.changeScene(scene);
        }
    }
}

