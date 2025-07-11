#include "Scene.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "SceneManager.h"


Scene::Scene() : m_engine(Engine::getInstance()), m_resourceManager(ResourceManager::getInstance()), m_sceneManager(SceneManager::getInstance())
{
    m_renderer = m_engine.getRenderer();
    m_windowWidth = m_engine.getWindowWidth();
    m_windowHeight = m_engine.getWindowHeight();
}


void Scene::clean()
{
    // 清理音效
    m_soundEffects.clear();
    m_soundEffectMap.clear();
    // 清理音乐
    m_music.clear();
    m_musicMap.clear();
}