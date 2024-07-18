#include"startmenu.h"
#include "stage1.h"
#include "stage2.h"
#include"reset.h"
int main(int argc, char* argv[]) {
    // 初始化SDL


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        // 处理初始化失败的情况
        return 1;
    }

    srand((unsigned int)time(NULL));
    realpath(argv[0], cwd);
    d[0].orDick = get_BMPSerface("dicks/dickhead.bmp");
    d[1].orDick = get_BMPSerface("dicks/dickhead1.bmp");
    d[2].orDick = get_BMPSerface("dicks/dickhead2.bmp");
    d[3].orDick = get_BMPSerface("dicks/dickhead3.bmp");
    SDL_Surface* bk = get_BMPSerface("dicks/bk.bmp");
    SDL_Surface* RD = get_BMPSerface("dicks/RD.bmp");
    window = SDL_CreateWindow("Rotate Dicks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, logical_width, logical_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, logical_width, logical_height);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, dick);
    Tbk =SDL_CreateTextureFromSurface(renderer, bk);
    TRD =SDL_CreateTextureFromSurface(renderer, RD);
   // setTransparentColor(d[0].orDick, 0, 0, 0);

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
initQblocks();
//stage2();
    while(1)
    {

    if(!startMenu())
    {
        end();
        return 0;
    }
int tmp =stage1();
    if(tmp == 0)
    {
        end();
        return 0;
    }
    if( tmp == 1 && (!stage1pass()) )
    {
        end();
        return 0;
    }

    }


}