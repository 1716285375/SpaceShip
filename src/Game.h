#ifndef GAME_H
#define GAME_H

#include "Scene.h"
#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

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
    TTF_Font* getTitleFont() const { return titleFont; }
    TTF_Font* getTextFont() const { return textFont; }
    int getFPS() const { return FPS; }
    void setRunning(bool running) { isRunning = running; }

    void renderText(const std::string& text, int x, int y, int fontSize, SDL_Color color, FontType fontType);

private:
    Game(); // 私有构造函数，禁止外部实例化
    Game(const Game&) = delete; // 禁止拷贝构造函数
    Game& operator=(const Game&) = delete; // 禁止拷贝赋值运算符
    
    TTF_Font* titleFont; // 标题字体
    TTF_Font* textFont; // 文本字体

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