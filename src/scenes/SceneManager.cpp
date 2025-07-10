#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    
}

void SceneManager::changeScene(const std::string &name)
{
    if (m_currentScene) {
        m_currentScene->onExit();
        m_sceneHistory.push(m_currentSceneName);
    }
    m_currentScene = createScene(name);
    m_currentSceneName = name;
    m_currentScene->onEnter();
}

void SceneManager::goBack()
{
    if (!m_sceneHistory.empty()) {
        std::string prevName = m_sceneHistory.top();
        m_sceneHistory.pop();

        if (m_currentScene) {
            m_currentScene->onExit();
        }
        m_currentScene = createScene(prevName);
        m_currentSceneName = prevName;
        m_currentScene->onEnter();
    }
}

void SceneManager::registerScene(const std::string &name, std::function<std::unique_ptr<Scene>()> creator)
{
    m_sceneCreators[name] = creator;
}

std::unique_ptr<Scene> SceneManager::createScene(const std::string &name)
{
    auto it = m_sceneCreators.find(name);
    if (it!= m_sceneCreators.end()) {
        return it->second();
    }
    return nullptr;
}
