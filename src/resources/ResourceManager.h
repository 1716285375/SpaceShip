#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resource.h"
#include "TextureResource.h"
#include "FontResource.h"
#include "MusicResource.h"
#include "SoundResource.h"
#include "AnimationResource.h"

#include <memory>
#include <unordered_map>
#include <string>
#include <SDL.h>


class ResourceManager {
    public:
        static ResourceManager& getInstance() {
            static ResourceManager rm;
            return rm;
        }

        void loadTexture(SDL_Renderer* renderer, const std::string& filePath);
        void loadFont(const std::string& filePath);
        void loadMusic(const std::string& filePath);
        void loadSound(const std::string& filePath);
        void loadAnimation(SDL_Renderer* renderer, const std::string& filePath);
        bool loadAll(SDL_Renderer* renderer, const std::string& filePath);
        void unloadAll();
        std::unordered_map<std::string, TextureResource*> getTextures() { return m_textures; }
        std::unordered_map<std::string, FontResource*> getFonts() { return m_fonts; }
        std::unordered_map<std::string, MusicResource*> getMusic() { return m_music; }
        std::unordered_map<std::string, SoundResource*> getSounds() { return m_sounds; }
        std::unordered_map<std::string, AnimationResource*> getAnimations() { return m_animations; }

    private:
        ResourceManager() {}
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ~ResourceManager();

        std::unordered_map<std::string, TextureResource*> m_textures;
        std::unordered_map<std::string, FontResource*> m_fonts;
        std::unordered_map<std::string, MusicResource*> m_music;
        std::unordered_map<std::string, SoundResource*> m_sounds;
        std::unordered_map<std::string, AnimationResource*> m_animations;

 
        struct SDLTextureSourceDeleter {
            void operator()(TextureResource* textureRes) const {
                auto texture = textureRes->getTexture();
                if (texture) {
                    // 假设这里是要释放 SDL_Texture 的逻辑
                    SDL_DestroyTexture(texture);
                }
                delete textureRes;
            }
        };
};
#endif // RESOURCEMANAGER_H