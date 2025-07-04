#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include <SDL.h>


class Game
{
public:
    Game();
    ~Game();
    void run();
    void init();
    void clean();
    void changeScene(Scene* scene);

    void handleEvent(SDL_Event* event);
    void update();
    void render();
protected:
private:
    bool isRunning = true; // 检查游戏是否正在运行
    Scene* currentScene = nullptr; // 当前场景
    SDL_Window* window = nullptr; // 窗口
    SDL_Renderer* renderer = nullptr; // 渲染器
    int windowWidth = 600; // 窗口宽度
    int windowHeight = 800; // 窗口高度
};

#endif