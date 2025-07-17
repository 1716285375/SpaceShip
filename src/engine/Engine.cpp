#include "Engine.h"
#include "MenuScene.h"
#include "utils.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <memory>
#include <string>
#include <iostream>
#include <spdlog/spdlog.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"


#ifdef _WIN32
#include <windows.h>        // SetProcessDPIAware()
#endif

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

Engine::Engine() : m_resourceManager(ResourceManager::getInstance()), m_sceneManager(SceneManager::getInstance())
{

}

Engine::~Engine()
{
    if (m_isRunning) {
        spdlog::info("Quitting engine...");
        quit();
    }
}



void Engine::init()
{
    main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0); // 默认缩放比例
    m_frameTime = 1000 / 60; // 16.66ms/帧
    // m_windowWidth = static_cast<int>(1280 * main_scale);
    // m_windowHeight = static_cast<int>(720 * main_scale);
    m_windowWidth = 1280;
    m_windowHeight = 720;
    m_isRunning = true;
    // SDL 初始化
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        spdlog::error("SDL could not initialize! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }
    // 创建窗口
    m_window = SDL_CreateWindow("Space Shoot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (m_window == nullptr) {
        spdlog::error("Window could not be created! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }

    // 加载图标
    SDL_Surface* icon = SDL_LoadBMP("../../assets/image/icon/app-icon.bmp");  // 替换为你的图标路径
    if (!icon) {
        spdlog::error("图标加载失败: {}", SDL_GetError());
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
        spdlog::error("Renderer could not be created! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }
    
    // 设置逻辑分辨率
    SDL_RenderSetLogicalSize(m_renderer, m_windowWidth, m_windowHeight);

    // 初始化SDL_image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        spdlog::error("SDL_image could not initialize! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }
    // 初始化SDL_ttf
    if (TTF_Init() == -1) {
        spdlog::error("SDL_ttf could not initialize! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }
    // 初始化SDL_mixer
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        spdlog::error("SDL_mixer could not initialize! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }

    // 打开音频设备
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2028) < 0) {
        spdlog::error("SDL_mixer could not open audio! SDL_Error: {}", SDL_GetError());
        m_isRunning = false;
    }
    Mix_AllocateChannels(32); // 设置最大音频通道数
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4); // 设置音量
    Mix_Volume(-1, MIX_MAX_VOLUME / 8);

    std::string resPath = "../../data/resources.json";
    bool isLoaded = m_resourceManager.loadAll(m_renderer, resPath);
    if (!isLoaded) {
        std::cout << "资源加载失败" << std::endl;
        m_isRunning = false;
    }
    m_sceneManager.registerScene("MenuScene", []() {
        return new MenuScene();
    });
    m_sceneManager.changeScene("MenuScene");


    // -------- ImGui 初始化必须在 SDL 初始化后 --------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io->Fonts->AddFontFromFileTTF("../../assets/font/Silver-48px.ttf", 16.0f);

    // 获取缩放比例
    main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);

    // ImGui 样式和缩放
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    // ImGui 后端初始化
    ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
    ImGui_ImplSDLRenderer2_Init(m_renderer);

}


void Engine::run()
{
    init();
    while(m_isRunning) {
        auto frameStart = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event); // 处理ImGui事件
            if (event.type == SDL_QUIT) {
                m_isRunning = false;
                break;
            } else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int w = event.window.data1;
                int h = event.window.data2;
                m_windowWidth = w;
                m_windowHeight = h;
                SDL_RenderSetLogicalSize(m_renderer, m_windowWidth, m_windowHeight); // 逻辑分辨率保持不变
                // // 通知 ImGui 新的显示尺寸
                // io->DisplaySize = ImVec2(float(w), float(h));
                
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_F1) {
                    show_demo_window = !show_demo_window;
                } else if (event.key.keysym.sym == SDLK_F2) {
                    show_another_window = !show_another_window;
                } else if (event.key.keysym.sym == SDLK_F3) {
                    m_debug = !m_debug;
                }
            }
            handleEvents(&event);
                
            // ImGui 新帧
            ImGui_ImplSDLRenderer2_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            // 示例窗口
            if (show_demo_window) {
                ImGui::ShowDemoWindow(&show_demo_window);
            }
            // 另一个窗口
            if (show_another_window) {
                ImGui::ShowDemoWindow(&show_another_window);
            }
            if (m_debug) {
                render_debug();
            }
            // 调试面板
            update(m_deltaTime);
            render();

            auto frameEnd = SDL_GetTicks(); // 记录当前时刻，返回毫秒(ms)
            auto diff = frameEnd - frameStart; // 计算两次时刻间隔
            if (diff < m_frameTime) {
                SDL_Delay(m_frameTime - diff);
                m_deltaTime = m_frameTime / 1000.0f;
            }
            else {
                m_deltaTime = diff / 1000.0f;
            }
        }
    }
}

void Engine::update(float deltaTime)
{
    m_sceneManager.getCurrentScene()->update(deltaTime);
}

void Engine::render()
{
    // Rendering

    SDL_RenderSetScale(m_renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(m_renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(m_renderer);

    if (m_showGrid) {
        drawGrid(m_renderer, 0, 0, getWindowWidth(), getWindowHeight(), m_cellSize, m_color);
    }

    // 渲染当前场景
    m_sceneManager.getCurrentScene()->render(m_renderer);
    
    // ImGui Rendering
    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer); 
    SDL_RenderPresent(m_renderer);
}

void Engine::handleEvents(SDL_Event *event)
{
    m_sceneManager.getCurrentScene()->handleInput(event);
}

void Engine::quit()
{
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

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

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Engine::render_debug() {

    ImGui::Begin("调试面板");
    ImGui::Checkbox("显示网格", &m_showGrid);
    ImGui::SameLine();
    ImGui::SliderInt("网格大小", &m_cellSize, 8, 256);
    ImGui::InputInt("##cellSize_input", &m_cellSize, 8, 256);
    if (ImGui::ColorEdit4("颜色", (float*)&m_ImColor)) {
        // 将 ImGui 颜色转换为 SDL_Color
        m_color.r = (Uint8)(m_ImColor.x * 255.0f);
        m_color.g = (Uint8)(m_ImColor.y * 255.0f);
        m_color.b = (Uint8)(m_ImColor.z * 255.0f);
        m_color.a = (Uint8)(m_ImColor.w * 255.0f);
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}