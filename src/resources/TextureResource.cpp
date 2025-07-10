#include "TextureResource.h"

TextureResource::TextureResource(SDL_Texture *texture, int w, int h) : m_texture(texture), m_w(w), m_h(h)
{
    
}

TextureResource::~TextureResource()
{
    unload();
}

void TextureResource::unload()
{
    if (m_texture) {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

}

int TextureResource::getWidth() const
{
    return m_w;
}

int TextureResource::getHeight() const
{
    return m_h;
}
