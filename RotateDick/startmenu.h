#ifndef ROTATEDICK_STARTMENU_H
#define ROTATEDICK_STARTMENU_H

#include "functions.h"
SDL_bool startMenu()
{
    SDL_Rect st = {446,400,78,78};

    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../audios/menu.wav");
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

        }
        SDL_RenderClear(renderer);

        SDL_RenderCopyEx(renderer, TRD, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &st, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);
    }
}


#endif //ROTATEDICK_STARTMENU_H