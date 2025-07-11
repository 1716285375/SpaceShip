#include "Scene.h"
#include "Engine.h"
#include "ResourceManager.h"


Scene::Scene() : m_renderer(Engine::getInstance().getRenderer()), m_resourceManager(ResourceManager::getInstance()),
    m_windowWidth(Engine::getInstance().getWindowWidth()), m_windowHeight(Engine::getInstance().getWindowHeight())
{
    
}
