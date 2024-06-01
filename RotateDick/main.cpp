#include<SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <libgen.h>
struct Dick
{
    double deg;
    SDL_Surface *orDick;
    SDL_bool isDick;
    SDL_Texture *Dtext;
    SDL_Rect DPos;
    int RotateTime;
};
struct Dick d[6];
int rnum;
int main(int argc, char* argv[]) {
    // 初始化SDL


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // 处理初始化失败的情况
        return 1;
    }
    int logical_width = 970;
    int logical_height = 545;
    char cwd[1024];
    char pdir[1024];
    realpath(argv[0], cwd);
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/dickhead.bmp");
    printf("%s",pdir);
    d[0].orDick = SDL_LoadBMP(pdir);
    
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/dickhead1.bmp");
    d[1].orDick = SDL_LoadBMP(pdir);
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/dickhead2.bmp");
    d[2].orDick = SDL_LoadBMP(pdir);
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/dickhead3.bmp");
    d[3].orDick = SDL_LoadBMP(pdir);
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/bk.bmp");
    SDL_Surface* bk = SDL_LoadBMP(pdir);
    SDL_Window* window = SDL_CreateWindow("Rotate Dicks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, logical_width, logical_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, logical_width, logical_height);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, dick);
    SDL_Texture *Tbk =SDL_CreateTextureFromSurface(renderer, bk);
    int spcX = 970;
    bool spcFirst=1;
    for (int i = 0; i < 4; i++) {
           d[i].isDick = SDL_FALSE;
           d[i].Dtext = SDL_CreateTextureFromSurface(renderer, d[i].orDick);
           d[i].deg = 0;
           d[i].RotateTime = 0;
           d[i].DPos.x = 100 + i * 200;
           d[i].DPos.y = 100;
           d[i].DPos.w = 78;
           d[i].DPos.h = 78;
       }
    if (window == NULL) {
        // 处理窗口创建失败的情况
        SDL_Log("Fail to create the window");
        SDL_Quit();
        return 1;
    }
    for(int i=0;i<4;i++)
        SDL_FreeSurface(d[i].orDick);
    SDL_bool running = SDL_TRUE;
    SDL_bool showDick = SDL_FALSE;

    SDL_Rect dick1 = {100,100,78,78};

   
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {


            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
                break;
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
                        rnum = rand() % 4;
                        spcFirst = 0;
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
                        spcFirst = 1;
                    }
                }        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);
        

    }

    // 清理资源

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
