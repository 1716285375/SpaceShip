#include "ResourceManager.h"
#include <fstream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include "spdlog/sinks/stdout_color_sinks.h"

using json = nlohmann::json;

void ResourceManager::loadTexture(SDL_Renderer *renderer, const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::error("Failed to open texture file {}", filePath.c_str());
    }
    json data;
    try {
        data = json::parse(file);
        file.close();
    } catch (const std::exception& e) {
        spdlog::error("Failed to parse texture file {}: {}", filePath.c_str(), e.what());
    }
    for (auto& [tag, path] : data.items()) {
        auto it = m_textures.find(tag);
        if (it != m_textures.end()) {
            continue;
        }
        std::string imagePath = path["file"].get<std::string>();
        int w = path["w"].get<int>();
        int h = path["h"].get<int>();

        SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath.c_str());
        if (!texture) {
            spdlog::error("Failed to load texture {}: {}", filePath.c_str(), SDL_GetError());
        }

        // SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        // spdlog::info("--- Loading texture {} from file: {} | w: {} | h: {}", tag, imagePath, w, h);

        m_textures[tag] = new TextureResource(texture, w, h);
    }
}

void ResourceManager::loadFont(const std::string &filePath)
{   
    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::error("Failed to open font file {}", filePath.c_str());
    }
    json data;
    try {
        data = json::parse(file);
    } catch (const std::exception& e) {
        spdlog::error("Failed to parse font file {}: {}", filePath.c_str(), e.what());
    }
    for (auto& [tag, path] : data.items()) {
        // spdlog::debug("Loading font with tag: {}", tag);
        auto it = m_fonts.find(tag);
        if ( it != m_fonts.end()) {
            continue;
        }
        std::string fontPath = path["file"].get<std::string>();
        int ptsize = path["size"].get<int>();
        bool bold = path["bold"].get<bool>();
        bool italic = path["italic"].get<bool>();
        std::string fontName = tag;
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), ptsize);
        if (!font) {
            spdlog::error("Failed to load font {}: {}", filePath.c_str(), SDL_GetError());
            font = nullptr;
        }
        // spdlog::info("--- Loading font {} from file: {} | ptsize: {} | bold: {} | italic: {} | fontName: {}", 
        //             tag, fontPath, ptsize, bold, italic, fontName);
        m_fonts[tag] = new FontResource(font, ptsize, bold, italic, fontName); 
    }
}

void ResourceManager::loadMusic(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::error("Failed to open texture file {}", filePath.c_str());
    }
    json data;
    try {
        data = json::parse(file);
        file.close();
    } catch (const std::exception& e) {
        spdlog::error("Failed to parse texture file {}: {}", filePath.c_str(), e.what());
    }
    for (auto& [tag, path] : data.items()) {
        auto it = m_music.find(tag);
        if (it != m_music.end()) {
            continue;
        }
        Mix_Music* music = Mix_LoadMUS(path["file"].get<std::string>().c_str());
        float volume = path["volume"].get<float>();
        if (!music) {
            spdlog::error("Failed to load music {}: {}", filePath.c_str(), SDL_GetError());
        }

        m_music[tag] = new MusicResource(music, volume);
    }


}

void ResourceManager::loadSound(const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::error("Failed to open texture file {}", filePath.c_str());
    }
    json data;
    try {
        data = json::parse(file);
        file.close();
    } catch (const std::exception& e) {
        spdlog::error("Failed to parse texture file {}: {}", filePath.c_str(), e.what());
    }
    for (auto& [tag, path] : data.items()) {
        auto it = m_sounds.find(tag);
        if (it != m_sounds.end()) {
            continue;
        }
        Mix_Chunk* sound = Mix_LoadWAV(path["file"].get<std::string>().c_str());
        float volume = path["volume"].get<float>();
        if (!sound) {
            spdlog::error("Failed to load sound {}: {}", filePath.c_str(), SDL_GetError());
        }
        m_sounds[tag] = new SoundResource(sound, volume);
    }

}

void ResourceManager::loadAnimation(SDL_Renderer* renderer, const std::string &filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        spdlog::error("Failed to open texture file {}", filePath.c_str());
    }
    json data;
    try {
        data = json::parse(file);
        file.close();
    } catch (const std::exception& e) {
        spdlog::error("Failed to parse texture file {}: {}", filePath.c_str(), e.what());
    }

    for (auto& [tag, path] : data.items()) {
        auto it = m_animations.find(tag);
        if (it != m_animations.end()) {
            continue;
        }
        std::string imagePath = path["image"].get<std::string>();
        SDL_Texture* texture = IMG_LoadTexture(renderer, imagePath.c_str());
        if (!texture) {
            spdlog::error("Failed to load texture {}: {}", filePath.c_str(), SDL_GetError());
        }
        int x = path["x"].get<int>();
        int y = path["y"].get<int>();
        int w = path["w"].get<int>();
        int h = path["h"].get<int>();
        int currentFrame = path["currentFrame"].get<int>();
        int totalFrames = path["totalFrames"].get<int>();
        float frameDuration = path["frameDuration"].get<float>();
        spdlog::info("--- Loading animation {} from file: {} | x: {} | y: {} | w: {} | h: {} | currentFrame: {} | totalFrames: {} | frameDuration: {} |",
                    tag, imagePath, x, y, w, h, currentFrame, totalFrames, frameDuration);
        Frame frames = {
            texture,
            x,
            y,
            w,
            h,
            currentFrame,
            totalFrames,
            frameDuration
        };
        Animation* animation = new Animation(&frames);
        m_animations[tag] = new AnimationResource(animation);
    }
}

bool ResourceManager::loadAll(SDL_Renderer* renderer, const std::string &filePath)
{
    try {
        std::ifstream file(filePath);
        spdlog::info("Loading resources from {}", filePath);
        if (!file.is_open()) {
            spdlog::error("Failed to open resource file {}", filePath.c_str());
        }
        json data;
        try {
            data = json::parse(file);
            file.close();
        } catch (const std::exception& e) {
            spdlog::error("Failed to parse resource file {}: {}", filePath.c_str(), e.what());
        }
        try {
            for (auto& [tag, path] : data.items()) {
                if (!path.is_string()) {
                        spdlog::error("Failed to load resources: path is not a string, but is {}", path.dump());
                        return false;
                }
                if (tag == "textures") {
                    spdlog::info("Loading textures from {}", path.get<std::string>());
                    loadTexture(renderer, path.get<std::string>());
                } else if (tag == "fonts") {
                    spdlog::info("Loading fonts from {}", path.get<std::string>());
                    loadFont(path.get<std::string>());
                } else if (tag == "music") {
                    spdlog::info("Loading music from {}", path.get<std::string>());
                    loadMusic(path.get<std::string>());
                } else if (tag == "sounds") {
                    spdlog::info("Loading sounds from {}", path.get<std::string>());
                    loadSound(path.get<std::string>());
                } else if (tag == "animations") {
                    spdlog::info("Loading animations from {}", path.get<std::string>());
                    loadAnimation(renderer, path.get<std::string>());
                }
                else {
                    spdlog::warn("Unknown resource type: {}", tag);
                }
            }
            return true;
        } catch (const std::exception& e) {
            spdlog::error("Failed to load resources: {}", e.what());
            return false;
        }

    } catch (const std::exception& e) {
        spdlog::error("Failed to open resource file {}: {}", filePath.c_str(), e.what());
        return false;
    }
}

void ResourceManager::unloadAll()
{
    m_textures.clear();
    m_fonts.clear();
    m_music.clear();
    m_sounds.clear();
    m_animations.clear();
}

ResourceManager::~ResourceManager()
{
    unloadAll();
}