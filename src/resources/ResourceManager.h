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
        std::unordered_map<std::string, std::unique_ptr<TextureResource>>& getTextures() { return m_textures; }
        std::unordered_map<std::string, std::unique_ptr<FontResource>>& getFonts() { return m_fonts; }
        std::unordered_map<std::string, std::unique_ptr<MusicResource>>& getMusic() { return m_music; }
        std::unordered_map<std::string, std::unique_ptr<SoundResource>>& getSounds() { return m_sounds; }
        std::unordered_map<std::string, std::unique_ptr<AnimationResource>>& getAnimations() { return m_animations; }

    private:
        ResourceManager() {}
        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;
        ~ResourceManager();

        std::unordered_map<std::string, std::unique_ptr<TextureResource>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<FontResource>> m_fonts;
        std::unordered_map<std::string, std::unique_ptr<MusicResource>> m_music;
        std::unordered_map<std::string, std::unique_ptr<SoundResource>> m_sounds;
        std::unordered_map<std::string, std::unique_ptr<AnimationResource>> m_animations;
};
#endif // RESOURCEMANAGER_H