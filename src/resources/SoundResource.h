#ifndef SOUND_RESOURCE_H
#define SOUND_RESOURCE_H

#include "Resource.h"
#include <SDL_mixer.h>

class SoundResource : public Resource {
    public:
        SoundResource(Mix_Chunk* chunk, float volume = 1.0f);
        ~SoundResource();
        virtual void unload() override;
        Mix_Chunk* getChunk() const;
    private:
        Mix_Chunk* m_chunk;
        float m_volume;
        
};

#endif // SOUND_RESOURCE_H
