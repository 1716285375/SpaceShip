#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>
#include <deque>

struct Player {
    SDL_Texture* texture = nullptr; // 玩家的贴图
    SDL_FPoint position{0, 0}; // 玩家的位置
    int width = 0; // 玩家的宽度
    int height = 0; // 玩家的高度
    int speed = 300; // 玩家的速度
    Uint32 coolDown = 300; // 玩家发射子弹的冷却时间
    Uint32 lastShootTime = 0; // 玩家上次射击的时间

    int health = 100; // 玩家的总生命值
    int currentHealth = 100; // 玩家当前的生命值
    int score = 0; // 玩家的得分

    std::deque<SDL_FPoint> trail; // 残影轨迹

};

struct Enemy {
    SDL_Texture* texture = nullptr; // 敌人的贴图
    SDL_FPoint position{0, 0}; // 敌人的位置
    int width = 0; // 敌人的宽度
    int height = 0; // 敌人的高度
    int speed = 200; // 敌人的速度
    Uint32 coolDown = 1000; // 敌人发射子弹的冷却时间
    Uint32 lastShootTime = 0; // 敌人上次射击的时间

    int damage = 10; // 敌人的伤害值
    int health = 100; // 敌人的总生命值
    int currentHealth = 100; // 敌人当前的生命值
};

struct ProjectileEnemy {
    SDL_Texture* texture = nullptr; // 敌人的子弹贴图
    SDL_FPoint position{0, 0}; // 敌人的子弹位置
    SDL_FPoint direction{0, 0}; // 敌人的子弹方向
    int width = 0; // 敌人的子弹宽度
    int height = 0; // 敌人的子弹高度
    int speed = 400; // 敌人的子弹速度
};

struct ProjectilePlayer {
    SDL_Texture* texture = nullptr; // 玩家的子弹贴图
    SDL_FPoint position{0, 0}; // 玩家的子弹位置
    int width = 0; // 玩家的子弹宽度
    int height = 0; // 玩家的子弹高度
    int speed = 500; // 玩家的子弹速度
    
    int damage = 40; // 玩家的子弹伤害值
};

#endif // OBJECT_H