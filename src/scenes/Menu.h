#ifndef MENU_H
#define MEN

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

class FontResource;
class TextureResource;

class MenuItem {
    public:
        MenuItem(SDL_Renderer* renderer, TextureResource* texture, const std::string& text, FontResource* font, int x, int y, int width, int height, SDL_Color color);
        ~MenuItem();

        void render();
        
    private:
        SDL_Renderer* m_renderer;
        TextureResource* m_texture;
        std::string m_text;
        FontResource* m_font;
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        SDL_Color m_color;
};

class Menu {
    public:
        Menu(SDL_Renderer* renderer, const std::vector<std::string>& menuItems);
        ~Menu();
        void addMenuItem(TextureResource* texture, const std::string& text, FontResource* font, int x, int y, int width, int height, SDL_Color color);
        void render();
    private:
        SDL_Renderer* m_renderer;
        std::vector<MenuItem*> m_menuItems;
        std::vector<std::string> m_menuItemTexts;
        int m_selectedItem;
        int m_selectedItemIndex;
        int m_selectedItemX;
        int m_selectedItemY;
        int m_selectedItemHeight;
        int m_selectedItemWidth;
        int m_totalMenuItems;
};

#endif // MENU_H