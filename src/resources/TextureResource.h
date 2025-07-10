#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "Resource.h"
#include <SDL.h>

class TextureResource : public Resource {
    public:
        TextureResource(SDL_Texture* texture, int width, int height);
        ~TextureResource();
        void unload() override;
        SDL_Texture* getTexture() const;
        int getWidth() const;
        int getHeight() const;

    private:
        SDL_Texture* m_texture;
        int m_width;
        int m_height;
};

#endif // TEXTURE_RESOURCE_H