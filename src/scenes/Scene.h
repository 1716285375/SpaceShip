#ifndef SCENE_H
#define SCENE_H


#include <SDL.h>

class ResourceManager;

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

protected:
    SDL_Renderer* getRenderer() const { return m_renderer; };
    ResourceManager& getResourceManager() const { return m_resourceManager; };
private:
    mutable SDL_Renderer* m_renderer;
    ResourceManager& m_resourceManager;
};
#endif // SCENE_H