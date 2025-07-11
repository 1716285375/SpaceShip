#ifndef SCENE_H
#define SCENE_H


#include <SDL.h>

class ResourceManager;
class Engine;

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

    int getWindowWidth() const { return m_windowWidth; };
    int getWindowHeight() const { return m_windowHeight; };
protected:
    SDL_Renderer* getRenderer() const { return m_renderer; };
    ResourceManager& getResourceManager() const { return m_resourceManager; };
private:
    mutable SDL_Renderer* m_renderer;
    ResourceManager& m_resourceManager;
    int m_windowWidth;
    int m_windowHeight;
};
#endif // SCENE_H