#include "EntityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto e = std::make_shared<Entity>(tag, m_totalEntities++);
    return e;
}

EntityPtr EntityManager::getEntities() const
{
    return EntityPtr();
}

EntityPtr EntityManager::getEntities(const std::string &tag) const
{
    return EntityPtr();
}
