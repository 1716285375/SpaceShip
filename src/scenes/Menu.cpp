#include "Menu.h"
#include "utils.h"
#include "TextureResource.h"
#include "FontResource.h"

MenuItem::MenuItem(SDL_Renderer *renderer, TextureResource *texture, const std::string &text, FontResource *font, int x, int y, int width, int height, SDL_Color color) :
    m_renderer(renderer), m_texture(texture), m_text(text), m_font(font), m_x(x), m_y(y), m_width(width), m_height(height), m_color(color)
{


}

MenuItem::~MenuItem()
{

}

void MenuItem::render()
{    
    // 渲染文字
    renderTextCenter(m_renderer, m_font->getFont(), m_text, m_x, m_y, m_color);
    
    // 渲染纹理
    SDL_Rect srcRectTexture = {
        0,
        0,
        m_texture->getWidth(),
        m_texture->getHeight()
    };
    SDL_Rect dstRectTexture = {
        m_x,
        m_y,
        m_texture->getWidth() * 2,
        m_texture->getHeight()
    };

    SDL_RenderCopy(m_renderer, m_texture->getTexture(), &srcRectTexture, &dstRectTexture);
}

Menu::Menu(SDL_Renderer *renderer, const std::vector<std::string>& menuItemTexts) :
    m_renderer(renderer), m_menuItemTexts(menuItemTexts)
{
    m_totalMenuItems = menuItemTexts.size();
}

Menu::~Menu()
{
    for (MenuItem* item : m_menuItems) {
        delete item;  // 释放每个 MenuItem 对象
    }
    m_menuItems.clear();  // 清空向量
}

void Menu::addMenuItem(TextureResource *texture, const std::string &text, FontResource *font, int x, int y, int width, int height, SDL_Color color)
{
    MenuItem* item = new MenuItem(m_renderer, texture, text, font, x, y, width, height, color);
    m_menuItems.push_back(item);
}

void Menu::render()
{
    for (auto& item : m_menuItems)
    {
        item->render();
    }
}