#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#include <stdio.h>
#include "ResourceManager.h"
#include "SceneManager.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"



class Engine final {
    public:
        static Engine& getInstance()
        {
            static Engine engine;
            return engine;
        }
        ~Engine();
        SDL_Window* getWindow() const { return m_window; };
        SDL_Renderer* getRenderer() const { return m_renderer; };
        void run();
        void init();
        void update(float deltaTime);
        void render();
        void handleEvents(SDL_Event* event);
        void quit();

        int getWindowWidth() const { return m_windowWidth; }
        int getWindowHeight() const { return m_windowHeight; }

        ResourceManager& getResourceManager() { return m_resourceManager; }
        SceneManager& getSceneManager() { return m_sceneManager; }

        void render_debug();
        

    private:
        Engine();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        ResourceManager& m_resourceManager;
        SceneManager& m_sceneManager;
        ImGuiIO* io = nullptr;
        float main_scale;
        bool m_isRunning = false;
        int m_windowWidth;
        int m_windowHeight;
        int m_frameRate;
        float m_deltaTime;
        bool show_demo_window = false;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
        float test_var = 0.0f;
        Uint32 m_frameTime; // 每帧时间
        bool m_debug = false;
        // bool m_initialized = false;

};

#endif //  ENGINE_H
