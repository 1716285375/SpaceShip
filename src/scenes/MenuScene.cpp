#include "MenuScene.h"
#include "LevelScene.h"
#include "HelpScene.h"
#include "OptionScene.h"
#include "SettingScene.h"
#include "QuitScene.h"
#include "utils.h"
#include "ResourceManager.h"
#include "SceneManager.h"

#include "SDL.h"
#include <spdlog/spdlog.h>
#include <iostream>

MenuScene::MenuScene() : m_numOptions(3), m_menu(new Menu(getRenderer(), m_optionTexts))
{

}

void MenuScene::update(float deltaTime)
{

}
void MenuScene::render(SDL_Renderer *renderer)
{
    renderText(renderer, m_mainFont->getFont(), "Space Shoot", Scene::getWindowWidth() / 2 -200, Scene::getWindowHeight() / 4 - 100, 400, 100, { 55, 149, 135, 255 });
    renderText(renderer, m_mainFont->getFont(), "Author: Jiecode CopyRight@2025 Version: 1.0.1", Scene::getWindowWidth() - 404, Scene::getWindowHeight() - 24, 400, 20, { 175, 221, 255, 255 });
    m_menu->render();
}

void MenuScene::handleInput(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                m_menu->selectItemUp();
                Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_change"], 0);
                break;
            case SDLK_DOWN:
                m_menu->selectItemDown();
                spdlog::info("Down key pressed");
                Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_change"], 0);
                break;
            case SDLK_LEFT:
                spdlog::info("Left key pressed");
                break;
            case SDLK_RIGHT:
                spdlog::info("Right key pressed");
                break;
            case SDLK_RETURN:
                spdlog::info("Enter key pressed");
                if (m_menu->getCurrentItemIndex() < 0) {
                    break;
                }
                Mix_PlayChannel(1, Scene::m_soundEffectMap["menu_select"], 0);
                Scene::getSceneManager().changeScene(m_optionSceneTexts[m_menu->getCurrentItemIndex()]);
                break;
        }
    } else if (event->type == SDL_MOUSEMOTION) {
        int x = event->motion.x;
        int y = event->motion.y;
        int selectedItem = m_menu->selectItem(x, y);
        static Uint32 lastPlayTime = 0; // 静态变量，存储上次播放时间
        static int selectedItemLast = -1; // 静态变量，存储上次选择的选项
        Uint32 currentTime = SDL_GetTicks();
        Uint32 timeSinceLastPlay = currentTime - lastPlayTime;
        Uint32 minInterval = 400; // 最小间隔 200 毫秒

        if (selectedItem != -1 && timeSinceLastPlay > minInterval && selectedItem != selectedItemLast) {
            Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_change"], 0);
            lastPlayTime = currentTime; // 更新上次播放时间
        }
        selectedItemLast = selectedItem; // 更新上次选择的选项
    } else if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;
        int selectedItem = m_menu->selectItem(x, y);
        if (selectedItem != -1) {
            Mix_PlayChannel(1, Scene::m_soundEffectMap["menu_select"], 0);
            Scene::getSceneManager().changeScene(m_optionSceneTexts[m_menu->getCurrentItemIndex()]);
        }
    } else if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
        for(size_t i = 0; i < m_optionTexts.size(); i++) {
            m_menu->updateMenuItem(m_optionTexts[i], Scene::getWindowWidth(), m_optionY * 3, 0, m_offsetY[i]);
        }
    }

}

void MenuScene::onEnter()
{
    spdlog::debug("Menu scene entered");
    Scene::getSceneManager().registerScene("LevelScene", []() {
        return new LevelScene();
    });
    Scene::getSceneManager().registerScene("HelpScene", []() {
        return new HelpScene();
    });
    Scene::getSceneManager().registerScene("OptionScene", []() {
        return new OptionScene();
    });
    Scene::getSceneManager().registerScene("SettingScene", []() {
        return new SettingScene();
    });
    Scene::getSceneManager().registerScene("QuitScene", []() {
        return new QuitScene();
    });
    std::string menuAsset = "../../data/scenes/menu/menu_scene.txt";
    std::string musicAsset = "../../data/scenes/menu/menu_music.txt";
    std::string soundAsset = "../../data/scenes/menu/menu_sound.txt";
    spdlog::info("Loading menu scene from {}", menuAsset);
    std::vector<std::string> tags = readTagsFromFile(menuAsset);
    std::vector<std::string> musicTags = readTagsFromFile(musicAsset);
    std::vector<std::string> soundTags = readTagsFromFile(soundAsset);
    for (const auto& tag : musicTags) {
        spdlog::info("Loading musicTag: {}", tag);
        MusicResource* music = Scene::getResourceManager().getMusic()[tag];
        Scene::m_music.push_back(music->getMusic());
        Scene::m_musicMap.insert(std::make_pair(tag, music->getMusic()));
        spdlog::debug("Music loaded: " + tag);
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME); // 设置音量

    for (const auto& tag : soundTags) {
        spdlog::info("Loading soundTag: {}", tag);
        SoundResource* sound = Scene::getResourceManager().getSounds()[tag];
        Scene::m_soundEffects.push_back(sound->getChunk());
        Scene::m_soundEffectMap.insert(std::make_pair(tag, sound->getChunk()));
        spdlog::debug("Sound effect loaded: " + tag);
    }

    Mix_Volume(0, MIX_MAX_VOLUME); // 设置音效音量
    Mix_Volume(1, MIX_MAX_VOLUME);

    // 获取一个 TextureResource 的 shared_ptr
    std::string textureTag = "banner_modern";
    TextureResource* texture = Scene::getResourceManager().getTextures()[textureTag];

    if (texture) {
        spdlog::info("Texture found: {}", textureTag);
    } else {
        spdlog::info("Texture not found: {}", textureTag);
    }

    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        spdlog::info("Font found: {}", fontTag);
    } else {
        spdlog::info("Font not found: {}", fontTag);
    }
    m_mainFont = Scene::getResourceManager().getFonts()["VonwaonBitmap-16px"];
    if (m_mainFont) {
        spdlog::info("Main font loaded: {}", m_mainFont->getFontName());
    } else {
        spdlog::info("Failed to load main font");
    }

    int offsetY = 0;
    for (auto& optionText: m_optionTexts) {
        m_offsetY.push_back(offsetY);
        m_menu->addMenuItem(texture, optionText, font, Scene::getWindowWidth(), m_optionY * 3, 0, offsetY, m_optionColor, m_selectedColor);
        offsetY += (font->getHeight() + 20); // 假设每个选项之间的间隔为50像素
    }

    Mix_PlayMusic(Scene::m_musicMap["bg_menu_scene"], -1); // 循环播放菜单音乐
}

void MenuScene::onExit()
{
    spdlog::debug("Menu scene exited");
    Mix_HaltMusic(); // 停止播放菜单音乐
    Scene::clean(); // 清理资源
    delete m_menu; // 删除菜单对象
    
}