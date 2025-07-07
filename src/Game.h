#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Object.h"
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
    void update(float deltaTime);
    void render();
    void changeScene(Scene* scene);
    void handleEvent(SDL_Event* event);

    void backgroundUpdate(float deltaTime);
    void renderBackground();   

    SDL_Window* getWindow() const { return window; }
    SDL_Renderer* getRenderer() const { return renderer; }
    int getWindowWidth() const { return windowWidth; }
    int getWindowHeight() const { return windowHeight; }
    void setRunning(bool running) { isRunning = running; }

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
    int FPS = 60; // 游戏帧率
    Uint32 frameTime; // 每帧时间
    float deltaTime; // 时间间隔

    Background nearStars; // 近处背景
    Background farStars; // 远处背景
};

#endif