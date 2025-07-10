#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include "Scene.h"
// 菜单场景
class MenuScene : public Scene {
    public:
        virtual void update(float deltaTime) override;
        virtual void render(SDL_Renderer* renderer) override;
        virtual void handleInput(const SDL_Event& event) override;
        virtual void onEnter() override;
        virtual void onExit() override;

    private:
        

};

#endif // MENU_SCENE_H