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
        // 获取单例实例
        static SceneManager& getInstance() {
            static SceneManager instance;
            return instance;
        }
        ~SceneManager();

        void changeScene(const std::string& name);
        void goBack();
        void registerScene(const std::string& name, std::function<std::unique_ptr<Scene>()> creator);
        std::unique_ptr<Scene>& getCurrentScene() {
            return m_currentScene;
        }
        std::string& getCurrentSceneName() {
            return m_currentSceneName;
        }

    private:
        SceneManager();
        // 禁止拷贝和赋值
        SceneManager(const SceneManager&) = delete;
        SceneManager& operator=(const SceneManager&) = delete;
        SDL_Renderer* m_renderer;
        std::unique_ptr<Scene> m_currentScene = nullptr;
        std::string m_currentSceneName;
        std::unique_ptr<Scene> m_nextScene = nullptr;
        std::stack<std::string> m_sceneHistory;
        std::unordered_map<std::string, std::function<std::unique_ptr<Scene>()>> m_sceneCreators;

        std::unique_ptr<Scene> createScene(const std::string& name);

};

#endif // SCENEMANAGER_H