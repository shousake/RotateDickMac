#ifndef ROTATEDICK_STAGE1_H
#define ROTATEDICK_STAGE1_H
#include "functions.h"
#include"reset.h"
#include "blocks.h"
int spcX = 970;
SDL_bool spcFirst=SDL_TRUE;
SDL_Rect r= {970,200 ,78,78};
int die();
int stage1pass();
int stage1();
int stage1()
{
    freeQuestionblocks();
    for(int i=0;i<4;i++)
    {
        addQBlocks(d[i].DPos.x+11,d[i].DPos.y-80,50,50,10,i);
    }
    load_WAV("audios/1.wav",SDL_TRUE);
    SDL_PauseAudio(0);
    SDL_bool win[4];
    for(int i=0;i<4;i++)
    {
        win[i]= SDL_FALSE;
    }
    //addNullBlock(0,0,50,50,9);
    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {


            if (event.type == SDL_QUIT)
            {

                return SDL_FALSE;
            }
            // 其它事件处理...

            if (event.type == SDL_MOUSEBUTTONDOWN )
            {
                for (int i=0;i<4;i++)
                {

                    if(event.button.x>100+i*200&&event.button.x<178+i*200&&event.button.y>100&&event.button.y<178)
                    {

                        d[i].isDick = SDL_TRUE;
                    }
                }


            }
            if (event.type == SDL_KEYDOWN )
            {


                if(event.key.keysym.sym == 'w')
                    {

                        d[0].isDick = SDL_TRUE;
                    }
                if(event.key.keysym.sym == 's')
                {

                    d[1].isDick = SDL_TRUE;
                }
                if(event.key.keysym.sym == 'a')
                {

                    d[2].isDick = SDL_TRUE;
                }
                if(event.key.keysym.sym == 'd')
                {

                    d[3].isDick = SDL_TRUE;
                }



            }

        }

        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, Tbk, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
        for (int i=0;i<4;i++)
        {
            SDL_RenderCopyEx(renderer, d[i].Dtext, NULL, &d[i].DPos, d[i].deg, NULL, SDL_FLIP_NONE);

            if(d[i].isDick == SDL_TRUE)
            {
                d[i].deg+=3;

            }
            if (d[i].deg>=360)
            {
                d[i].deg = 0;
                d[i].isDick = SDL_FALSE;
                d[i].RotateTime++;
            }


        }
        putQblock();
        putNullBlocks();
        if (d[0].RotateTime >= 4 && d[1].RotateTime >= 4 && d[2].RotateTime >= 4 && d[3].RotateTime >= 4)
        {
            if (spcFirst)
            {
                if(win[0]&&win[1]&&win[2]&&win[3])
                {

                    SDL_CloseAudio();
                    return SDL_TRUE;
                }

                rnum = rand() % 4;
                DeleteQblock(rnum);
                addNullBlock(d[rnum].DPos.x+11,d[rnum].DPos.y-80,50,50,rnum);
                win[rnum] = SDL_TRUE;
                spcFirst = SDL_FALSE;
            }

           r.x=spcX;
            SDL_RenderCopyEx(renderer, d[rnum].Dtext, NULL, &r, d[rnum].deg, NULL, SDL_FLIP_NONE);
            spcX--;
            if (spcX <= 0)
            {
                for (int i = 0; i < 4; i++)
                {
                    d[i].RotateTime -= 4;

                }
                spcX = 970;
                spcFirst = SDL_TRUE;
            }
        }
        if((!spcFirst)&&(!d[0].isDick)&&(!d[1].isDick)&&(!d[2].isDick)&&(!d[3].isDick))
        {
            SDL_CloseAudio();


            if(!die())
            {
                return  SDL_FALSE;
            }
            return 2;
        }
        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);


    }
}


int stage1pass()
{
    load_WAV("audios/1pass.wav",SDL_FALSE);
    SDL_PauseAudio(0);
    reset();
  for(int j=0;j<4;j++)
  {
      while(d[j].DPos.y<560)
      {
          SDL_Event event;
          if (SDL_PollEvent(&event))
          {
              if (event.type == SDL_QUIT) {
                  SDL_CloseAudio();
                  return SDL_FALSE;
              }
          }

      SDL_RenderClear(renderer);
      SDL_RenderCopyEx(renderer, Tbk, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

      for (int i=0;i<4;i++)
      {
          SDL_RenderCopyEx(renderer, d[i].Dtext, NULL, &d[i].DPos, d[i].deg, NULL, SDL_FLIP_NONE);

      }
      d[j].DPos.y+=4;
      d[j].deg+=15;
      SDL_RenderPresent(renderer); // 更新屏幕显示
      SDL_Delay(10);
      }
  }
  reset();
  SDL_CloseAudio();
  return SDL_TRUE;
}
int die()
{
    double speed = -8;
    load_WAV("audios/dick_dies_2.wav",SDL_FALSE);
    SDL_PauseAudio(0);
    reset();
    double deg=0;
        while(r.y<600)
        {
            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT) {
                    SDL_CloseAudio();
                    return SDL_FALSE;
                }
            }

            SDL_RenderClear(renderer);
            SDL_RenderCopyEx(renderer, Tbk, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(renderer, d[rnum].Dtext, NULL, &r, deg, NULL, SDL_FLIP_NONE);
            for (int i=0;i<4;i++)
            {
                SDL_RenderCopyEx(renderer, d[i].Dtext, NULL, &d[i].DPos, 0, NULL, SDL_FLIP_NONE);

            }
            r.y+=speed;
            deg+=15;
            speed += 0.2;
            SDL_RenderPresent(renderer); // 更新屏幕显示
            SDL_Delay(10);
        }
    for (int i=0;i<20;i++)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                SDL_CloseAudio();
                return SDL_FALSE;
            }
        }
        SDL_Delay(10);
    }
    spcFirst=SDL_TRUE;
    spcX = 970;
    r.y = 200;
    reset();
    SDL_CloseAudio();
    return SDL_TRUE;
}

#endif //ROTATEDICK_STAGE1_H
