#include "MenuScene.h"
#include "utils.h"
#include "ResourceManager.h"

#include "SDL.h"
#include <iostream>

MenuScene::MenuScene() : m_numOptions(6), m_menu(std::make_unique<Menu>(getRenderer(), m_optionTexts))
{

}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::render(SDL_Renderer *renderer)
{
    m_menu->render();
}

void MenuScene::handleInput(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
                std::cout << "Up key pressed" << std::endl;
                break;
            case SDLK_DOWN:
                std::cout << "Down key pressed" << std::endl;
                break;
            case SDLK_LEFT:
                std::cout << "Left key pressed" << std::endl;
                break;
            case SDLK_RIGHT:
                std::cout << "Right key pressed" << std::endl;
                break;
            case SDLK_RETURN:
                std::cout << "Enter key pressed" << std::endl;
                break;
        }
    }
}

void MenuScene::onEnter()
{
    std::string menuAsset = "../../data/scenes/menu_scene.txt";
    std::cout << "Loading menu scene from " << menuAsset << std::endl;
    std::vector<std::string> tags = readTagsFromFile(menuAsset);
    auto &textures = Scene::getResourceManager().getTextures();
    TextureResource* textureRes = nullptr;
    for (auto& tag : tags) {
        auto it = textures.find(tag);
        if (it != textures.end()) {
            std::cout << "Found texture " << tag << std::endl;
            TextureResource& texture = *it->second;
            textureRes = &texture;
            // 现在你可以使用 texture 引用
        } else {
            std::cout << "Texture: [" << tag << "] not found" << std::endl;
        }
    }
    auto& fonts = Scene::getResourceManager().getFonts();
    auto it = fonts.find("Silver");
    if (it != fonts.end()) {
        std::cout << "Found font Silver" << std::endl;
        FontResource& font = *it->second;
        m_mainFont = &font;
    } else {
        std::cout << "Font [Silver] not found" << std::endl;
    }
    int offsetY = 0;
    for (auto& optionText: m_optionTexts) {
        m_menu->addMenuItem(textureRes, optionText, m_mainFont, Scene::getWindowWidth(), m_optionY*2 + offsetY, 100, 100, m_optionColor);
        offsetY += m_mainFont->getHeight() * 2; // 假设每个选项之间的间隔为50像素
    }
}

void MenuScene::onExit()
{
    std::cout << "Menu scene exited" << std::endl;
}