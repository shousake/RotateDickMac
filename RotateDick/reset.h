
#ifndef ROTATEDICK_RESET_H
#define ROTATEDICK_RESET_H
#include "functions.h"
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
#endif //ROTATEDICK_RESET_H
