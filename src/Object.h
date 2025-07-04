#ifndef OBJECT_H
#define OBJECT_H

#include <SDL.h>

struct Player {
    SDL_Texture* texture = nullptr; // 玩家的贴图
    SDL_FPoint position{0, 0}; // 玩家的位置
    int width = 0; // 玩家的宽度
    int height = 0; // 玩家的高度
    int speed = 0; // 玩家的速度
};

#endif