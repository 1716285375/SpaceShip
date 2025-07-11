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
    else if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;
        std::cout << "Mouse button pressed at (" << x << ", " << y << ")" << std::endl;
        int selectedItem = m_menu->selectItem(x, y);
        if (selectedItem != -1) {
            std::cout << "Selected menu item: " << selectedItem << std::endl;
            // 处理选中项的逻辑
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
        continue;
    }
    std::string tag = "banner_modern";
    auto itTexture = textures.find(tag);
    if (itTexture != textures.end()) {
        std::cout << "Found texture " << tag << std::endl;
        TextureResource& texture = *itTexture->second;
        textureRes = &texture;
    } else {
        std::cout << "Texture: [" << tag << "] not found" << std::endl;
    }

    auto& fonts = Scene::getResourceManager().getFonts();
    auto itFont = fonts.find("Silver");
    if (itFont != fonts.end()) {
        std::cout << "Found font Silver" << std::endl;
        FontResource& font = *itFont->second;
        m_mainFont = &font;
    } else {
        std::cout << "Font [Silver] not found" << std::endl;
    }
    int offsetY = 0;
    for (auto& optionText: m_optionTexts) {
        m_menu->addMenuItem(textureRes, optionText, m_mainFont, Scene::getWindowWidth(), m_optionY*2 + offsetY, 100, 100, m_optionColor, m_selectedColor);
        offsetY += m_mainFont->getHeight() * 2; // 假设每个选项之间的间隔为50像素
    }
}

void MenuScene::onExit()
{
    std::cout << "Menu scene exited" << std::endl;
}