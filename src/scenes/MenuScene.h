#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"


#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class FontResource;

class MenuItem {
    public:
        MenuItem(SDL_Texture* texture, const std::string& text, TTF_Font* font, int x, int y, int width, int height, int margin, SDL_Color color);
        ~MenuItem();
        void render(SDL_Renderer* renderer);
    
    private:
        SDL_Texture* m_texture;
        std::string m_text;
        TTF_Font* m_font;
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_margin;
        SDL_Color m_color;
};

class Menu {
    public:
        Menu(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<std::string>& options, TTF_Font* font, int x, int y, int width, int height, int margin, SDL_Color color);
        ~Menu();

        void render(SDL_Renderer* renderer);
    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;
        std::vector<std::shared_ptr<MenuItem>> m_items;
        TTF_Font* m_font;
                // 菜单选项
        enum class MenuOption {
            Play,
            Media,
            Option,
            Setting,
            Help,
            Exit,
            None
        };
        MenuOption m_currentOption = MenuOption::None;
        std::string m_currentText = "";
        // 菜单选项的位置
        int m_optionPos;
        // 菜单选项的位置X
        int m_optionPosX = 0;
        // 菜单选项的位置Y
        int m_optionPosY = 0;
        // 菜单选项的宽度
        const int m_optionWidth = 200;
        // 菜单选项的高度
        const int m_optionHeight = 50;
        // 菜单选项的间距
        const int m_optionMargin = 10;

        // 菜单选项的文字
        const std::vector<std::string> m_optionTexts = {
            "Play",
            "Media",
            "Options",
            "Settings",
            "Help",
            "Exit"
        };
        SDL_Color m_color;
};

// 菜单场景
class MenuScene : public Scene {
    public:
        MenuScene();
        virtual void update(float deltaTime) override;
        virtual void render(SDL_Renderer* renderer) override;
        virtual void handleInput(SDL_Event* event) override;
        virtual void onEnter() override;
        virtual void onExit() override;

    private:
        FontResource* m_mainFont;
        FontResource* m_subFont;

        // 菜单选项的数量
        const int m_numOptions;

        // 菜单选项的颜色
        const SDL_Color m_optionColors = {255, 255, 255, 255};
        Menu* m_menu;
        const SDL_Color m_selectedColor = {255, 0, 0, 255};
        
        

};

#endif // MENU_SCENE_H