#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <deque>

enum class ItemType {
    Life,
    Shield,
    Time
};

// 道具
struct Item {
    SDL_Texture* texture = nullptr; // 道具的贴图
    SDL_FPoint position{0, 0}; // 道具的位置
    SDL_FPoint direction{0, 0}; // 道具的方向
    int width = 0; // 道具的宽度
    int height = 0; // 道具的高度
    int speed = 200; // 道具的速度
    int bounceCount = 3; // 道具的反弹次数
    ItemType type = ItemType::Life; // 道具的类型
};

// 玩家
struct Player {
    SDL_Texture* texture = nullptr; // 玩家的贴图
    SDL_FPoint position{0, 0}; // 玩家的位置
    int width = 0; // 玩家的宽度
    int height = 0; // 玩家的高度
    int speed = 300; // 玩家的速度
    Uint32 coolDown = 200; // 玩家发射子弹的冷却时间
    Uint32 lastShootTime = 0; // 玩家上次射击的时间

    int health = 100; // 玩家的总生命值
    int currentHealth = 100; // 玩家当前的生命值
    int score = 0; // 玩家的得分

    std::deque<SDL_FPoint> trail; // 残影轨迹

};

// 敌人
struct Enemy {
    SDL_Texture* texture = nullptr; // 敌人的贴图
    SDL_FPoint position{0, 0}; // 敌人的位置
    int width = 0; // 敌人的宽度
    int height = 0; // 敌人的高度
    int speed = 200; // 敌人的速度
    Uint32 coolDown = 2000; // 敌人发射子弹的冷却时间
    Uint32 lastShootTime = 0; // 敌人上次射击的时间

    int health = 100; // 敌人的总生命值
    int currentHealth = 100; // 敌人当前的生命值
    int damage = 20; // 敌人的伤害值
};

// 敌人子弹
struct ProjectileEnemy {
    SDL_Texture* texture = nullptr; // 敌人的子弹贴图
    SDL_FPoint position{0, 0}; // 敌人的子弹位置
    SDL_FPoint direction{0, 0}; // 敌人的子弹方向
    int width = 0; // 敌人的子弹宽度
    int height = 0; // 敌人的子弹高度
    int speed = 400; // 敌人的子弹速度

    int damage = 10; // 敌人的伤害值
};

// 玩家子弹
struct ProjectilePlayer {
    SDL_Texture* texture = nullptr; // 玩家的子弹贴图
    SDL_FPoint position{0, 0}; // 玩家的子弹位置
    int width = 0; // 玩家的子弹宽度
    int height = 0; // 玩家的子弹高度
    int speed = 500; // 玩家的子弹速度

    int damage = 80; // 玩家的子弹伤害值
};

// 爆炸
struct Explosion {
    SDL_Texture* texture = nullptr; // 爆炸的贴图
    SDL_FPoint position{0, 0}; // 爆炸的位置
    int width = 0; // 爆炸的宽度
    int height = 0; // 爆炸的高度
    int currentFrame = 0; // 爆炸的当前帧
    int totalFrames = 0; // 爆炸的总帧数
    Uint32 startTime = 0; // 爆炸的开始时间
    Uint32 FPS = 10; // 爆炸的帧率
};

// 背景
struct Background {
    SDL_Texture* texture = nullptr; // 背景的贴图
    SDL_FPoint position{0, 0}; // 背景的位置
    float offset = 0; // 背景的偏移量
    int width = 0; // 背景的宽度
    int height = 0; // 背景的高度
    int speed = 30; // 背景的速度
};

#endif // OBJECT_H