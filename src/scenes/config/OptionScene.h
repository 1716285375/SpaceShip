#ifndef OPTION_SCENE_H
#define OPTION_SCENE_H

#include "Scene.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class OptionScene : public Scene {
    public:
        OptionScene();
        ~OptionScene();
        virtual void update(float deltaTime) override;
        virtual void render(SDL_Renderer* renderer) override;
        virtual void handleInput(SDL_Event* event) override;
        virtual void onEnter() override; //进入场景
        virtual void onExit() override; //退出场景

    private:
};



#endif // OPTION_SCENE_H