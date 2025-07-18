#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include "Entity.h"


using EntityVec = std::vector<Entity>;
using EntityPtr = std::shared_ptr<Entity>;
using EntityMap = std::map<std::string, EntityPtr>;

class EntityManager {

    public:
        EntityManager();
        ~EntityManager();
        std::shared_ptr<Entity> addEntity(const std::string& tag);
        EntityPtr getEntities() const;
        EntityPtr getEntities(const std::string& tag) const;

    private:
        EntityPtr m_entities;
        EntityMap m_entityMap;
        size_t m_totalEntities;


};

#endif // ENTITY_MANAGER_H