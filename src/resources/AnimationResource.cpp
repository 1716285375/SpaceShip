#include "AnimationResource.h"

AnimationResource::AnimationResource(Animation *animation) : m_animation(animation)
{

}

AnimationResource::~AnimationResource()
{
    unload();
}

void AnimationResource::unload()
{
    if (m_animation) {
        delete m_animation;
        m_animation = nullptr;
    }
}

Animation *AnimationResource::getAnimation() const
{
    if (m_animation) {
        return m_animation;
    }
    return nullptr;
}

Animation::Animation(Frame *frame)
{
}

Animation::~Animation()
{
}
