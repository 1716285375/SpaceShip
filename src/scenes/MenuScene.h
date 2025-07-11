#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"
#include "Menu.h"

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>

class FontResource;

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
        // 菜单选项的文本
        const std::vector<std::string> m_optionTexts = {
            "Play",
            "Option",
            "Setting",
            "Help",
            "Quit"
        };

        const std::vector<std::string> m_optionSceneTexts = {
            "LevelScene",
            "OptionScene",
            "SettingScene",
            "HelpScene",
            "QuitScene"
        };

        // 菜单选项的位置
        const int m_optionX = Scene::getWindowWidth();
        const int m_optionY = 100;
        // 菜单选项的颜色
        const SDL_Color m_optionColor = {255, 255, 255, 255};
        Menu* m_menu;
        const SDL_Color m_selectedColor = {255, 0, 0, 255};
        
        

};

#endif // MENU_SCENE_H