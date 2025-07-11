#ifndef SCENE_H
#define SCENE_H


#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <vector>

class ResourceManager;
class Engine;
class SceneManager;

//场景基类
class Scene
{
public:
    Scene();
    virtual ~Scene() { clean(); };
    virtual void update(float deltaTime) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void handleInput(SDL_Event* event) = 0;
    virtual void onEnter() {}; //进入场景
    virtual void onExit() {}; //退出场景
    void clean(); //清理资源

    int getWindowWidth() const { return m_windowWidth; };
    int getWindowHeight() const { return m_windowHeight; };
protected:
    SDL_Renderer* getRenderer() const { return m_renderer; };
    ResourceManager& getResourceManager() const { return m_resourceManager; };
    SceneManager& getSceneManager() const { return m_sceneManager; };
    std::vector<Mix_Chunk*> m_soundEffects;
    std::vector<Mix_Music*> m_music;
    std::unordered_map<std::string, Mix_Chunk*> m_soundEffectMap; // 音效映射
    std::unordered_map<std::string, Mix_Music*> m_musicMap; // 音乐映射
    TTF_Font* m_sceneFont_; // 字体
private:
    Engine& m_engine;
    SDL_Renderer* m_renderer;
    ResourceManager& m_resourceManager;
    SceneManager& m_sceneManager;
    int m_windowWidth;
    int m_windowHeight;

};
#endif // SCENE_H