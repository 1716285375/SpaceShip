#include "TextureResource.h"

TextureResource::TextureResource(SDL_Texture *texture, int width, int height) : m_texture(texture), m_width(width), m_height(height)
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
    return m_width;
}

int TextureResource::getHeight() const
{
    return m_height;
}
