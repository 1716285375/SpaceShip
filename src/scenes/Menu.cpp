#include "Menu.h"
#include "utils.h"
#include "TextureResource.h"
#include "FontResource.h"

MenuItem::MenuItem(SDL_Renderer *renderer, TextureResource* texture, const std::string &text, FontResource* font,
    int x, int y, int width, int height, SDL_Color normalColor, SDL_Color selectedColor) :
    m_renderer(renderer), m_texture(texture), m_text(text), m_font(font),
    m_x(x), m_y(y), m_width(width), m_height(height), m_normalColor(normalColor), m_selectedColor(selectedColor)
{
    m_isSelected = false; // 默认未选中
}

MenuItem::~MenuItem()
{

}

void MenuItem::render()
{    

    // 渲染纹理
    SDL_Rect srcRectTexture = {
        0,
        0,
        m_texture->getWidth(),
        m_texture->getHeight()
    };
    SDL_Rect dstRectTexture = {
        (m_x - m_texture->getWidth()) / 2,
        m_y - 2,
        m_texture->getWidth(),
        m_texture->getHeight()
    };

    SDL_RenderCopy(m_renderer, m_texture->getTexture(), NULL, &dstRectTexture);
    // 渲染文字
    SDL_Color textColor = m_isSelected? m_selectedColor : m_normalColor;
    renderTextCenter(m_renderer, m_font->getFont(), m_text, m_x, m_y, textColor);

    m_fontRect = dstRectTexture;
}

bool MenuItem::select(int x, int y)
{
    if (x >= m_fontRect.x && x <= m_fontRect.x + m_fontRect.w && y >= m_fontRect.y && y <= m_fontRect.y + m_fontRect.h) {
        m_isSelected = true;
        return true;
    }
    m_isSelected = false;
    return false;
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

void Menu::addMenuItem(TextureResource* texture, const std::string &text, FontResource* font, int x, int y, int width, int height, SDL_Color normalColor, SDL_Color selectedColor)
{
    MenuItem* item = new MenuItem(m_renderer, texture, text, font, x, y, width, height, normalColor, selectedColor);
    m_menuItems.push_back(item);
}

int Menu::selectItem(int x, int y)
{
    int selectedIndex = -1;
    for (int i = 0; i < m_totalMenuItems; i++) {
        if (m_menuItems[i]->select(x, y)) {
            selectedIndex = i;
            m_selectedItemIndex = selectedIndex;
        }
    }
    for (auto& item : m_menuItems) {
        item->deselect(); // 取消所有项的选中状态
    }
    m_menuItems[m_selectedItemIndex]->select();
    return selectedIndex;
}

void Menu::selectItemUp()
{
    if (m_selectedItemIndex > 0) {
        m_selectedItemIndex--;
    } else {
        m_selectedItemIndex = m_totalMenuItems - 1; // 循环到最后一个
    }
    for (auto& item : m_menuItems) {
        item->deselect(); // 取消所有项的选中状态
    }
    m_menuItems[m_selectedItemIndex]->select();
}

void Menu::selectItemDown()
{
    if (m_selectedItemIndex < m_totalMenuItems - 1) {
        m_selectedItemIndex++;
    } else {
        m_selectedItemIndex = 0; // 循环到第一个
    }
    for (auto& item : m_menuItems) {
        item->deselect(); // 取消所有项的选中状态
    }
    m_menuItems[m_selectedItemIndex]->select();
}

void Menu::render()
{
    for (auto& item : m_menuItems)
    {
        item->render();
    }
}