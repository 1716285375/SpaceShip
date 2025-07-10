#include "MusicResource.h"

MusicResource::MusicResource(Mix_Music *music, float volume) : m_music(music), m_volume(volume)
{

}

MusicResource::~MusicResource()
{
    unload();
}

Mix_Music *MusicResource::getMusic() const
{
    if (m_music) {
        return m_music;
    }
    return nullptr;
}

void MusicResource::unload()
{
    if (m_music) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}
