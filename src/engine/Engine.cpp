#include "Engine.h"
#include "MenuScene.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <memory>
#include <string>


Engine::Engine() : m_resourceManager(ResourceManager::getInstance()), m_sceneManager(SceneManager::getInstance())
{

}

Engine::~Engine()
{
}



void Engine::init()
{
    m_frameTime = 1000 / 60; // 16.66ms/帧
    m_windowWidth = 1280;
    m_windowHeight = 720;
    m_isRunning = true;
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    // 创建窗口
    m_window = SDL_CreateWindow("Space Shoot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }

    // 加载图标
    SDL_Surface* icon = SDL_LoadBMP("../../assets/image/icon/app-icon.bmp");  // 替换为你的图标路径
    if (!icon) {
        SDL_Log("图标加载失败: %s", SDL_GetError());
        // 即使图标加载失败，也可以继续运行程序
    }
    else {
        // 设置窗口图标
        SDL_SetWindowIcon(m_window, icon);
        // 释放表面资源
        SDL_FreeSurface(icon);
    }


    // 创建渲染器
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    
    // 设置逻辑分辨率
    SDL_RenderSetLogicalSize(m_renderer, m_windowWidth, m_windowHeight);
    // 初始化SDL_image
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_image could not initialize! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    // 初始化SDL_ttf
    if (TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_ttf could not initialize! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    // 初始化SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not initialize! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }

    // 打开音频设备
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not open audio! SDL_Error: %s\n", SDL_GetError());
        m_isRunning = false;
    }
    Mix_AllocateChannels(32); // 设置最大音频通道数
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 8);

    std::string resPath = "../../data/resources.json";
    m_resourceManager.loadAll(m_renderer, resPath);
    m_sceneManager.registerScene("MenuScene", []() {
        return std::unique_ptr<MenuScene>(new MenuScene());
    });
    m_sceneManager.changeScene("MenuScene");

}


void Engine::run()
{
    init();
    while(m_isRunning) {
        auto frameStart = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_isRunning = false;
                break;
            }
            handleEvents(&event);
        }
        update(m_deltaTime);
        render();

        auto frameEnd = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        auto diff = frameEnd - frameStart; // 计算两次时刻间隔
        if (diff < m_frameTime)
        {
            SDL_Delay(m_frameTime - diff);
            m_deltaTime = m_frameTime / 1000.0f;
        }
        else
        {
            m_deltaTime = diff / 1000.0f;
        }
    }
}

void Engine::update(float deltaTime)
{
    m_sceneManager.getCurrentScene()->update(deltaTime);
}

void Engine::render()
{
    SDL_RenderClear(m_renderer);
    m_sceneManager.getCurrentScene()->render(m_renderer);
    SDL_RenderPresent(m_renderer);
}

void Engine::handleEvents(SDL_Event *event)
{
    m_sceneManager.getCurrentScene()->handleInput(event);
}

void Engine::quit()
{
    if (m_window != nullptr) {
        SDL_DestroyWindow(m_window);
    }
    if (m_renderer!= nullptr) {
        SDL_DestroyRenderer(m_renderer);
    }
    // 清理SDL_image
    IMG_Quit();
    // 清理SDL_ttf
    TTF_Quit();
    // 清理SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
    // 清理SDL
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
