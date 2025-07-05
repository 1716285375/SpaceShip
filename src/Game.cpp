#include "Game.h"
#include "SceneMain.h"
#include <SDL.h>
#include <SDL_image.h>


Game::Game()
{
    
}

Game::~Game()
{
    clean();
}


void Game::init()
{
    frameTime = 1000 / 60; // 16.66ms/帧
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建窗口
    window = SDL_CreateWindow("Space Shoot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        isRunning = false;
    }
    // 创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    }

    // 初始化SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
    }
    // 切换到主场景
    currentScene = new SceneMain();
    currentScene->init();
}


void Game::run()
{
    while (isRunning)
    {
        auto frameStart = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        SDL_Event event;
        handleEvent(&event);

        update(deltaTime);

        render();
        auto frameEnd = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        auto diff = frameEnd - frameStart; // 计算两次时刻间隔
        if (diff < frameTime)
        {
            SDL_Delay(frameTime - diff);
            deltaTime = frameTime / 1000.0f;
        }
        else
        {
            deltaTime = diff / 1000.0f;
        }
    }
}

void Game::clean()
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::changeScene(Scene *scene)
{
    if (currentScene != nullptr)
    {
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}


void Game::handleEvent(SDL_Event* event)
{
    while (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
        {
            isRunning = false;
        }
        currentScene->handleEvent(event);
    }
}
void Game::update(float deltaTime)
{
    currentScene->update(deltaTime);
}
void Game::render()
{
    // 清空
    SDL_RenderClear(renderer);
    // 渲染场景
    currentScene->render();
    // 显示渲染结果
    SDL_RenderPresent(renderer);
}