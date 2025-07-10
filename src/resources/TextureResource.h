#ifndef TEXTURE_RESOURCE_H
#define TEXTURE_RESOURCE_H

#include "Resource.h"
#include <SDL.h>

class TextureResource : public Resource {
    public:
        TextureResource(SDL_Texture* texture, int w, int h);
        ~TextureResource();
        void unload() override;
        SDL_Texture* getTexture() const { return m_texture; };
        int getWidth() const;
        int getHeight() const;

    private:
        SDL_Texture* m_texture;
        int m_w;
        int m_h;
};

#endif // TEXTURE_RESOURCE_H