#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>

//场景基类
class Scene
{
public:
    Scene();
    virtual ~Scene() = default;
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleInput(SDL_Event* event) = 0;
    virtual void onEnter() {}; //进入场景
    virtual void onExit() {}; //退出场景
};
#endif // SCENE_H