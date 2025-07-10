#include "MenuScene.h"

#include "SDL.h"
#include <iostream>

void MenuScene::update(float deltaTime)
{
}

void MenuScene::render(SDL_Renderer *renderer)
{
    SDL_Color color = { 255, 0, 0, 255 }; // 设置颜色为红色 (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { 0, 0, 200, 200 }; // 定义矩形的位置和大小
    SDL_RenderFillRect(renderer, &rect); // 填充矩形
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 设置颜色为黑色 (R, G, B, A)
}

void MenuScene::handleInput(SDL_Event* event)
{
}

void MenuScene::onEnter()
{
}

void MenuScene::onExit()
{
}
