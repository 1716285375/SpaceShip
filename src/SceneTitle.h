#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H


#include "Scene.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class Game; // 前向声明 Game 类

class SceneTitle: public Scene {
public:
    ~SceneTitle();
    virtual void init() override;
    virtual void update(float deltaTime) override;
    virtual void render() override;
    virtual void clean() override;
    virtual void handleEvent(SDL_Event* event) override;

private:
    Mix_Music* bgMusic; // 背景音乐
    float timer = 0.0f; // 计时器


};

#endif // SCENE_TITLE_H