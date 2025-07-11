#include "Scene.h"
#include "Engine.h"
#include "ResourceManager.h"


Scene::Scene() : m_engine(Engine::getInstance()), m_resourceManager(ResourceManager::getInstance())
{
    m_renderer = m_engine.getRenderer();
    m_windowWidth = m_engine.getWindowWidth();
    m_windowHeight = m_engine.getWindowHeight();
}
