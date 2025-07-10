#ifndef ANIMATION_RESOURCE_H
#define ANIMATION_RESOURCE_H

#include "Resource.h"
#include <SDL.h>

struct Frame {
    SDL_Texture* texture;
    int x;
    int y;
    int w;
    int h;
    int currentFrame;
    int totalFrames;
    float frameDuration;
};

class Animation {
    public:
        Animation(Frame* frame);
        ~Animation();
        // void update(int elapsedTime);
        // void render(int x, int y, int width, int height, double angle, SDL_RendererFlip flip);
    
    private:
        Frame* m_frame;
};

class AnimationResource : public Resource {
    public:
        AnimationResource(Animation* animation);
        ~AnimationResource();
        void unload() override;
        Animation* getAnimation() const;
    
    private:
        Animation* m_animation;
};
#endif // ANIMATION_RESOURCE_H