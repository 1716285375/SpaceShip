#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#include "ResourceManager.h"
#include "SceneManager.h"


class Engine {
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
        

    private:
        Engine();
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        ResourceManager& m_resourceManager;
        SceneManager& m_sceneManager;
        bool m_isRunning = false;
        int m_windowWidth;
        int m_windowHeight;
        int m_frameRate;
        float m_deltaTime;
        Uint32 m_frameTime; // 每帧时间
        // bool m_initialized = false;

};

#endif //  ENGINE_H
