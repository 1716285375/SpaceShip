#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>
#include <random>


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

    void keyboardControl(float deltaTime); // 键盘控制

    void shootPlayer(); // 玩家射击
    void updatePlayerProjectiles(float deltaTime); // 玩家子弹更新
    void renderPlayerProjectiles(); // 玩家子弹渲染

    void spawnEnemy();  // 敌人生成
    void updateEnemies(float deltaTime); // 敌人更新
    void renderEnemies(); // 敌人渲染
    void shootEnemy(Enemy* enemy); // 敌人射击
    void updateEnemyProjectiles(float deltaTime); // 敌人子弹更新
    void renderEnemyProjectiles(); // 敌人子弹渲染

    void enemyExplode(Enemy* enemy); // 敌人爆炸效果

    SDL_FPoint getDirection(Enemy* enemy); // 获取敌人方向

private:
    Game& game; // 游戏对象

    Enemy enemyTemplate; // 敌人对象模板
    ProjectileEnemy projectileEnemyTemplate; // 敌人子弹对象模板
    std::list<Enemy*> enemies; // 敌人对象列表
    std::list<ProjectileEnemy*> projectilesEnemy; // 敌人子弹对象列表

    Player player; // 玩家对象
    ProjectilePlayer projectilePlayerTemplate; // 玩家子弹对象模板
    std::list<ProjectilePlayer*> projectilesPlayer; // 玩家子弹对象列表

    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器，用于生成随机的 x 坐标

};

#endif