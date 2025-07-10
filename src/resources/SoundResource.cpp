#include "SoundResource.h"

SoundResource::SoundResource(Mix_Chunk *chunk, float volume) : m_chunk(chunk), m_volume(volume)
{
    
}

SoundResource::~SoundResource()
{
    unload();
}

void SoundResource::unload()
{
    if (m_chunk) {
        Mix_FreeChunk(m_chunk);
        m_chunk = nullptr;
    }
}

Mix_Chunk *SoundResource::getChunk() const
{
    if (m_chunk) {
        return m_chunk;
    }
    return nullptr;
}
