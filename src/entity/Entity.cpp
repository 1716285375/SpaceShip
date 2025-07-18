#include "Entity.h"


Entity::Entity()
{

}

// void Entity::add<T>(args) {

// }

// T& Entity::get<T>() {

// }
size_t Entity::id() const {
    return 0;
}
bool Entity::isAlive() const {
    return true;
}
void Entity::destroy() {

}

const std::string& Entity::tag() const {
    return m_tag;
}