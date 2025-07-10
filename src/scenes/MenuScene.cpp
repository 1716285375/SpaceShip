#include "MenuScene.h"
#include "utils.h"
#include "ResourceManager.h"

#include "SDL.h"
#include <iostream>

MenuScene::MenuScene() : m_numOptions(6)
{

}

void MenuScene::update(float deltaTime)
{

}

void MenuScene::render(SDL_Renderer *renderer)
{
    for (auto& optionText: m_optionTexts) {
        SDL_SetRenderDrawColor(renderer, m_optionColors.r, m_optionColors.g, m_optionColors.b, m_optionColors.a);
        auto it = Scene::getResourceManager().getTextures().find("banner_modern");
        auto& textRes = *it->second;
        SDL_Texture* texture = textRes.getTexture();
        SDL_Rect srcRect = {
            m_optionPosX,
            m_optionPosY,
            textRes.getWidth(),
            textRes.getHeight()
        };

        SDL_Rect dstRect = {
            m_optionPosX,
            m_optionPosY,
            textRes.getWidth() * 2,
            textRes.getHeight() * 1
        };
        SDL_RenderCopy(Scene::getRenderer(), texture, &srcRect, &dstRect);
    
    }
    SDL_Color color = { 255, 0, 0, 255 }; // 设置颜色为红色 (R, G, B, A)
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { 0, 0, 200, 200 }; // 定义矩形的位置和大小
    SDL_RenderFillRect(renderer, &rect); // 填充矩形
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 设置颜色为黑色 (R, G, B, A)
}

void MenuScene::handleInput(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDL_Scancode::SDL_SCANCODE_UP:
                std::cout << "Up key pressed" << std::endl;
                break;
            case SDL_Scancode::SDL_SCANCODE_DOWN:
                std::cout << "Down key pressed" << std::endl;
                break;
            case SDL_Scancode::SDL_SCANCODE_LEFT:
                std::cout << "Left key pressed" << std::endl;
                break;
            case SDL_Scancode::SDL_SCANCODE_RIGHT:
                std::cout << "Right key pressed" << std::endl;
                break;
            case SDL_Scancode::SDL_SCANCODE_RETURN:
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
    for (auto& tag : tags) {
        auto it = textures.find(tag);
        if (it != textures.end()) {
            std::cout << "Found texture " << tag << std::endl;
            // TextureResource& texture = *it->second;
            // 现在你可以使用 texture 引用
        }
        else {
            std::cout << "Texture " << tag << " not found" << std::endl;
        }
    }
    auto& fonts = Scene::getResourceManager().getFonts();
    auto it = fonts.find("Silver");
    if (it != fonts.end()) {
        std::cout << "Found font Silver" << std::endl;
        FontResource& font = *it->second;
        m_mainFont = &font;
    }
}

void MenuScene::onExit()
{

}

MenuItem::MenuItem(SDL_Texture *texture, const std::string &text, TTF_Font *font, int x, int y, int width, int height, int margin, SDL_Color color)
{
    m_texture = texture;
    m_text = text;
    m_font = font;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_margin = margin;
    m_color = color;
}

MenuItem::~MenuItem()
{

}

void MenuItem::render(SDL_Renderer *renderer)
{

}

Menu::Menu(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<std::string> &options, TTF_Font *font, int x, int y, int width, int height, int margin, SDL_Color color)
{
    for (auto& option : options) {
        m_items.push_back(std::make_shared<MenuItem>(texture, option, font, x, y, width, height, margin, color));
        y += height + margin;
    }
}

Menu::~Menu()
{
}

void Menu::render(SDL_Renderer *renderer)
{
    for (auto& item: m_items) {
        item->render(renderer);
    }
}