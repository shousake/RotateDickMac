//
// Created by shousake on 2024/12/10.
//
#include "reset.h"  // 包含头文件，确保声明一致

void reset()
{
    for (int i = 0; i < 4; i++) {
        d[i].isDick = SDL_FALSE;
        d[i].deg = 0;
        d[i].RotateTime = 0;
        d[i].DPos.x = 100 + i * 200;
        d[i].DPos.y = 100;
        d[i].DPos.w = 78;
        d[i].DPos.h = 78;
    }
}