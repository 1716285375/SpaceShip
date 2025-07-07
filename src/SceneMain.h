#ifndef SCENE_MAIN_H
#define SCENE_MAIN_H

#include "Scene.h"
#include "Object.h"
#include <list>
#include <map>
#include <random>
#include <SDL_mixer.h>


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

    void updatePlayer(float deltaTime); // 玩家更新
    void shootPlayer(); // 玩家射击
    void updatePlayerProjectiles(float deltaTime); // 玩家子弹更新
    void renderPlayerProjectiles(); // 玩家子弹渲染
    void playerGetItem(Item* item); // 玩家获得道具

    void spawnEnemy();  // 敌人生成
    void updateEnemies(float deltaTime); // 敌人更新
    void renderEnemies(); // 敌人渲染
    void shootEnemy(Enemy* enemy); // 敌人射击
    void updateEnemyProjectiles(float deltaTime); // 敌人子弹更新
    void renderEnemyProjectiles(); // 敌人子弹渲染

    void enemyExplode(Enemy* enemy); // 敌人爆炸效果
    void updateExplosions(float deltaTime); // 爆炸更新
    void renderExplosions(); // 爆炸渲染

    void dropItem(Enemy* enemy); // 道具掉落
    void updateItems(float deltaTime); // 道具更新
    void renderItems(); // 道具渲染

    void renderUI(); // 渲染 UI 元素

    SDL_FPoint getDirection(Enemy* enemy); // 获取敌人方向

private:
    Game& game; // 游戏对象
    Mix_Music* bgMusic; // 背景音乐
    SDL_Texture* uiHealth; // 生命值 UI 元素

    Enemy enemyTemplate; // 敌人对象模板
    ProjectileEnemy projectileEnemyTemplate; // 敌人子弹对象模板
    std::list<Enemy*> enemies; // 敌人对象列表
    std::list<ProjectileEnemy*> projectilesEnemy; // 敌人子弹对象列表

    bool isDead = false; // 玩家是否死亡
    Player player; // 玩家对象
    ProjectilePlayer projectilePlayerTemplate; // 玩家子弹对象模板
    std::list<ProjectilePlayer*> projectilesPlayer; // 玩家子弹对象列表

    Explosion explosionTemplate; // 爆炸对象模板
    std::list<Explosion*> explosions; // 爆炸对象列表

    Item itemTemplate; // 道具对象模板
    std::list<Item*> items; // 道具对象列表

    std::map<std::string, Mix_Chunk*> sounds; // 存储声音

    std::mt19937 gen; // 随机数生成器
    std::uniform_real_distribution<float> dis; // 随机数分布器，用于生成随机的 x 坐标

};

#endif