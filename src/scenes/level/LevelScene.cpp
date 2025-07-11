#include "LevelScene.h"


#include <SDL.h>
#include <SDL_image.h>
#include <spdlog/spdlog.h>

LevelScene::LevelScene()
{

}

LevelScene::~LevelScene()
{
}

void LevelScene::handleInput(SDL_Event* event)
{

}

void LevelScene::update(float deltaTime)
{

}

void LevelScene::render(SDL_Renderer* renderer)
{
    if (!renderer) {
        spdlog::error("Renderer is null in LevelScene::render");
        return;
    }
    // 渲染逻辑
    SDL_Rect dstRect = {
        0,
        0,
        100,
        100
    };
    SDL_RenderDrawRect(renderer, &dstRect);
}

void LevelScene::onEnter()
{
    spdlog::info("Enter LevelScene");

}

void LevelScene::onExit()
{
    spdlog::info("Exit LevelScene");
}