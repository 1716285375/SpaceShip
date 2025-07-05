#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>

struct Player {
    SDL_Texture* texture = nullptr; // 玩家的贴图
    SDL_FPoint position{0, 0}; // 玩家的位置
    int width = 0; // 玩家的宽度
    int height = 0; // 玩家的高度
    int speed = 200; // 玩家的速度
    Uint32 coolDown = 500; // 玩家发射子弹的冷却时间
    Uint32 lastShootTime = 0; // 玩家上次射击的时间

};

struct ProjectilePlayer {
    SDL_Texture* texture = nullptr; // 玩家的子弹贴图
    SDL_FPoint position{0, 0}; // 玩家的子弹位置
    int width = 0; // 玩家的子弹宽度
    int height = 0; // 玩家的子弹高度
    int speed = 500; // 玩家的子弹速度
};

#endif // OBJECT_H