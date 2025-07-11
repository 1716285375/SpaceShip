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
                Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_select"], 0);
                break;
            case SDLK_DOWN:
                m_menu->selectItemDown();
                std::cout << "Down key pressed" << std::endl;
                Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_select"], 0);
                break;
            case SDLK_LEFT:
                std::cout << "Left key pressed" << std::endl;
                break;
            case SDLK_RIGHT:
                std::cout << "Right key pressed" << std::endl;
                break;
            case SDLK_RETURN:
                std::cout << "Enter key pressed" << std::endl;
                Scene::getSceneManager().changeScene(m_optionSceneTexts[m_menu->getCurrentItemIndex()]);
                Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_select"], 0);
                break;
        }
    }
    else if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;
        std::cout << "Mouse button pressed at (" << x << ", " << y << ")" << std::endl;
        int selectedItem = m_menu->selectItem(x, y);
        if (selectedItem != -1) {
            std::cout << "Selected menu item: " << selectedItem << std::endl;
            Scene::getSceneManager().changeScene(m_optionSceneTexts[m_menu->getCurrentItemIndex()]);
            Mix_PlayChannel(0, Scene::m_soundEffectMap["menu_select"], 0);
            // 处理选中项的逻辑
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
    std::cout << "Loading menu scene from " << menuAsset << std::endl;
    std::vector<std::string> tags = readTagsFromFile(menuAsset);
    std::vector<std::string> musicTags = readTagsFromFile(musicAsset);
    std::vector<std::string> soundTags = readTagsFromFile(soundAsset);
    for (const auto& tag : musicTags) {
        std::cout << "Loading musicTag: " << tag << std::endl;
        MusicResource* music = Scene::getResourceManager().getMusic()[tag];
        Scene::m_music.push_back(music->getMusic());
        Scene::m_musicMap.insert(std::make_pair(tag, music->getMusic()));
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME); // 设置音量

    for (const auto& tag : soundTags) {
        std::cout << "Loading soundTag: " << tag << std::endl;
        SoundResource* sound = Scene::getResourceManager().getSounds()[tag];
        Scene::m_soundEffects.push_back(sound->getChunk());
        Scene::m_soundEffectMap.insert(std::make_pair(tag, sound->getChunk()));
    }

    Mix_Volume(0, MIX_MAX_VOLUME);

    // 获取一个 TextureResource 的 shared_ptr
    std::string textureTag = "banner_modern";
    TextureResource* texture = Scene::getResourceManager().getTextures()[textureTag];

    if (texture) {
        std::cout << "Texture found: " << textureTag << std::endl;
    } else {
        std::cout << "Texture not found: " << textureTag << std::endl;
    }

    std::string fontTag = "Silver-48px";
    FontResource* font = Scene::getResourceManager().getFonts()[fontTag];
    if (font) {
        std::cout << "Font found: " << fontTag << std::endl;
    } else {
        std::cout << "Font not found: " << fontTag << std::endl;
    }
    m_mainFont = Scene::getResourceManager().getFonts()["VonwaonBitmap-16px"];
    if (m_mainFont) {
        std::cout << "Main font loaded: " << m_mainFont->getFontName() << std::endl;
    } else {
        std::cout << "Failed to load main font" << std::endl;
    }

    int offsetY = 0;
    for (auto& optionText: m_optionTexts) {
        m_menu->addMenuItem(texture, optionText, font, Scene::getWindowWidth(), m_optionY * 3 + offsetY, 100, 100, m_optionColor, m_selectedColor);
        offsetY += (font->getHeight() + 20); // 假设每个选项之间的间隔为50像素
    }
    m_menu->getMenuItems()[m_menu->getCurrentItemIndex()]->select(); // 默认选中第一个菜单项

    Mix_PlayMusic(Scene::m_musicMap["bg_menu_scene"], -1); // 循环播放菜单音乐
}

void MenuScene::onExit()
{
    spdlog::debug("Menu scene exited");
    Mix_HaltMusic(); // 停止播放菜单音乐
    Scene::clean(); // 清理资源
    delete m_menu; // 删除菜单对象
    
}