#ifndef CTRANSFORM_H
#define CTRANSFORM_H

#include "Component.h"
#include <glm/glm.hpp>


class CTransform : public Component {
    public:
        CTransform();
        ~CTransform() {};
        void update() override;
    
    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
};

#endif // CTRANSFORM_H