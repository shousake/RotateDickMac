#ifndef ROTATEDICK_STAGE1_H
#define ROTATEDICK_STAGE1_H
#include "functions.h"
#include"reset.h"
SDL_bool stage1()
{
    int spcX = 970;
    SDL_bool spcFirst=SDL_TRUE;
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../audios/1.wav");
    if (SDL_LoadWAV(pdir, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        SDL_Log("Could not open wav file: %s\n", SDL_GetError());
        return SDL_FALSE;
    }

    audio.start = wav_buffer;
    audio.pos = wav_buffer;
    audio.length = wav_length;
    audio.total_length = wav_length;
    wav_spec.callback = audio_callback;
    wav_spec.userdata = &audio;
    if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    {
        SDL_Log("SDL_OpenAudio failed: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);

        return SDL_FALSE;
    }
    SDL_PauseAudio(0);

    SDL_bool win[4];

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
                //showDick = (SDL_bool)(showDick^1);
                //event.button.x>10 && event.button.x<88&&event.button.y>100&&event.button.y<178
                //&&event.tfinger.x<88&&event.tfinger.y>100&&event.tfinger.y<178)

                for (int i=0;i<4;i++)
                {

                    if(event.button.x>100+i*200&&event.button.x<178+i*200&&event.button.y>100&&event.button.y<178)
                    {
                        d[i].isDick = SDL_TRUE;
                    }
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
                win[rnum] = SDL_TRUE;
                spcFirst = SDL_FALSE;
            }

            SDL_Rect r = {spcX,200 ,78,78};
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
        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);


    }
}


SDL_bool stage1pass()
{
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../audios/1pass.wav");
    if (SDL_LoadWAV(pdir, &wav_spec, &wav_buffer, &wav_length) == NULL) {
        SDL_Log("Could not open wav file: %s\n", SDL_GetError());
        return SDL_FALSE;
    }

    audio.start = wav_buffer;
    audio.pos = wav_buffer;
    audio.length = wav_length;
    audio.total_length = wav_length;
    wav_spec.callback = audio_callback_once;
    wav_spec.userdata = &audio;
    if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    {
        SDL_Log("SDL_OpenAudio failed: %s\n", SDL_GetError());
        SDL_FreeWAV(wav_buffer);

        return SDL_FALSE;
    }
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


#endif //ROTATEDICK_STAGE1_H
