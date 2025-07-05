#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>

class Game; // 前向声明 Game 类

class SceneMain : public Scene {
public:
    SceneMain();
    ~SceneMain();

    void update(float deltaTime) override;
    void render() override;
    void handleEvent(SDL_Event* event) override;
    void init() override;
    void clean() override;

    void keyboardControl(float deltaTime);
    void shootPlayer();
    void updatePlayerProjectiles(float deltaTime);
    void renderPlayerProjectiles();

private:
    Game& game; // 游戏对象
    Player player; // 玩家对象

    ProjectilePlayer projectilePlayerTemplate; // 玩家子弹对象模板
    std::list<ProjectilePlayer*> projectilesPlayer; // 玩家子弹对象列表
};

#endif