//
// Created by shousake on 2024/7/4.
//
#include "functions.h"
#include"blocks.h"
#include "reset.h"
#ifndef ROTATEDICK_STAGE2_H
#define ROTATEDICK_STAGE2_H
//flappy dick
typedef struct
{
    int x;
    int y;
} Pos;

int stage2();
int die2();
int stage2pass();
//extern double Yspeed;
//extern SDL_Rect character;
//extern Pos pos;
//extern double accelerate;
#endif //ROTATEDICK_STAGE2_H
