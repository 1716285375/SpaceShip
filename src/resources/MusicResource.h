#ifndef MUSIC_RESOURCE_H
#define MUSIC_RESOURCE_H


#include "Resource.h"
#include <SDL_mixer.h>

class MusicResource : public Resource {
    public:
        MusicResource(Mix_Music* music, float volume = 1.0f);
        virtual ~MusicResource() override;

        Mix_Music* getMusic() const;

        virtual void unload() override;

    private:
        Mix_Music* m_music;
        float m_volume;

};

#endif // MUSIC_RESOURCE_H