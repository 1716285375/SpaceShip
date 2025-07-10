#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <memory>
#include <stack>
#include <string>
#include <functional>

// 场景管理器核心接口
class SceneManager {
    public:
        SceneManager();
        ~SceneManager();

        void changeScene(const std::string& name);
        void goBack();
        void registerScene(const std::string& name, std::function<std::unique_ptr<Scene>()> creator);



    private:
        SDL_Renderer* m_renderer;
        std::unique_ptr<Scene> m_currentScene;
        std::string m_currentSceneName;
        std::unique_ptr<Scene> m_nextScene;
        std::stack<std::string> m_sceneHistory;
        std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneCreators;

        std::unique_ptr<Scene> createScene(const std::string& name);

};

#endif // SCENEMANAGER_H