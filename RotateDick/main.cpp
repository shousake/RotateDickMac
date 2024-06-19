#include"startmenu.h"
#include "stage1.h"
#include"reset.h"
int main(int argc, char* argv[]) {
    // 初始化SDL


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        // 处理初始化失败的情况
        return 1;
    }

    srand((unsigned int)time(NULL));
    realpath(argv[0], cwd);
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/dickhead.bmp");

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
    strcpy(pdir, dirname(cwd));
    strcat(pdir, "/../dicks/RD.bmp");
    SDL_Surface* RD = SDL_LoadBMP(pdir);
    window = SDL_CreateWindow("Rotate Dicks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, logical_width, logical_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, logical_width, logical_height);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, dick);
    Tbk =SDL_CreateTextureFromSurface(renderer, bk);
    TRD =SDL_CreateTextureFromSurface(renderer, RD);
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

    while(1)
    {

    if(!startMenu())
    {
        end();
        return 0;
    }
    if(!stage1())
    {
        end();
        return 0;
    }
    if(!stage1pass())
    {
        end();
        return 0;
    }

    }

    // 清理资源
    end();

    return 0;
}