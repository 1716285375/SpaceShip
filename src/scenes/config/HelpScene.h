#ifndef HELP_SCENE_H
#define HELP_SCENE_H

#include "Scene.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class HelpScene : public Scene {
    public:
        HelpScene();
        ~HelpScene();
        virtual void update(float deltaTime) override;
        virtual void render(SDL_Renderer* renderer) override;
        virtual void handleInput(SDL_Event* event) override;
        virtual void onEnter() override; //进入场景
        virtual void onExit() override; //退出场景

    private:
};



#endif // HELP_SCENE_H