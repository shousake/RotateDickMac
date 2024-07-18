//
// Created by shousake on 2024/7/4.
//
#include "functions.h"
#ifndef ROTATEDICK_STAGE2_H
#define ROTATEDICK_STAGE2_H
int stage2()
{
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../pic/night.bmp");
    SDL_Texture *night = get_BMPTexture("pic/night.bmp");
    double deg=0;
    SDL_Rect rect = {900,80,78,78};
    SDL_bool showDick = SDL_TRUE ;
    //SDL_Surface *reSur = d[0].orDick;
   // flipHorizontal(reSur);
   // SDL_Texture *reText= SDL_CreateTextureFromSurface(renderer,reSur);
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
               // SDL_CloseAudio();
                return SDL_FALSE;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN )
            {
                showDick = SDL_FALSE;
            }
        }

        rect.x -- ;
        deg -= 2;
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, night, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
        if (showDick)
            SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &rect, deg, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);
    }
}
#endif //ROTATEDICK_STAGE2_H
