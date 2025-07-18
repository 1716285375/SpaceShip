#ifndef ENTITY_H
#define ENTITY_H


#include "Component.h"
#include "CTransform.h"

#include <tuple>
#include <string>
#include <vector>
#include <memory>
#include <map>


using ComponentTuple = std::tuple<
  CTransform

>;

class Entity {

    public:
        Entity();
        // void add<T>(args);
        // T& get<T>();
        size_t id() const;
        bool isAlive() const;
        void destroy();
        const std::string& tag() const;
    private:
        ComponentTuple        m_components;
        bool                  m_active = true;
        std::string           m_tag;
        size_t                m_id = 0;
};



#endif // ENTITY_H