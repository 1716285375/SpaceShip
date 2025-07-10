#include "Scene.h"
#include "Engine.h"
#include "ResourceManager.h"


Scene::Scene() : m_renderer(Engine::getInstance().getRenderer()), m_resourceManager(ResourceManager::getInstance())
{
    
}
