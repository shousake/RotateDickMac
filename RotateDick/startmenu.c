//
// Created by shousake on 2024/12/10.
//
#include "startmenu.h"
int startMenu()
{
    SDL_Rect st = {446,400,78,78};
    load_WAV("audios/menu.wav",SDL_TRUE);
    SDL_PauseAudio(0);
    
    addQBlocks(290,400,50,50,10,6);
    addQBlocks(630,400,50,50,10,1);
    SDL_Texture *hide = get_BMPTexture("pic/ds2.bmp");


    while (1)
    {

        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return SDL_FALSE;
            }
            if (event.button.x>446&&event.button.x<446+78&&event.button.y>400&&event.button.y<478)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN )
                {
                    st.h=78;
                    st.w=78;
                    st.x=446;
                    st.y=400;
                    double speed=1;
                    for(double deg=0;deg<360*6;deg+=speed)
                    {

                        if (SDL_PollEvent(&event))
                        {
                            if (event.type == SDL_QUIT) {
                                SDL_CloseAudio();
                                return SDL_FALSE;
                            }
                        }
                        if (speed<30)
                        {
                            speed += 0.02;
                        }
                        SDL_RenderClear(renderer);

                        SDL_RenderCopyEx(renderer, TRD, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

                        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &st, deg, NULL, SDL_FLIP_NONE);

                        SDL_RenderPresent(renderer); // 更新屏幕显示
                        SDL_Delay(10);
                    }
                    freeQuestionblocks();
                    freeObjects();
                    SDL_CloseAudio();
                    return SDL_TRUE;
                }
                st.h=98;
                st.w=98;
                st.x=436;
                st.y=390;
            }
            else
            {
                st.h=78;
                st.w=78;
                st.x=446;
                st.y=400;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(isPos(290,400,50,50,event)|| isPos(630,400,50,50,event))
                {
                    for(int i=0;i<200;i++)
                    {
                        if (SDL_PollEvent(&event))
                        {
                            if (event.type == SDL_QUIT) {
                                return SDL_FALSE;
                            }
                        }
                        SDL_RenderClear(renderer);
                        SDL_RenderCopyEx(renderer, hide, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderPresent(renderer); // 更新屏幕显示
                        SDL_Delay(10);
                    }

                }
            }
        }
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, TRD, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &st, 0, NULL, SDL_FLIP_NONE);
        putQblock();

        SDL_RenderPresent(renderer); // 更新屏幕显示

        SDL_Delay(10);
    }
   

}