#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <SDL.h>


class Game
{
public:
    static Game& getInstance()
    {
        static Game instance;
        return instance;
    }
    ~Game();
    
    void init();
    void run();
    void clean();
    void update();
    void render();
    void changeScene(Scene* scene);
    void handleEvent(SDL_Event* event);


    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }

private:
    Game(); // 私有构造函数，禁止外部实例化
    Game(const Game&) = delete; // 禁止拷贝构造函数
    Game& operator=(const Game&) = delete; // 禁止拷贝赋值运算符
    
    bool isRunning = true; // 检查游戏是否正在运行
    Scene* currentScene = nullptr; // 当前场景
    SDL_Window* window = nullptr; // 窗口
    SDL_Renderer* renderer = nullptr; // 渲染器
    int windowWidth = 600; // 窗口宽度
    int windowHeight = 800; // 窗口高度
};

#endif