//
// Created by shousake on 2024/12/10.
//
#include "stage2.h"
double Yspeed;
SDL_Rect character={0,0,78,78};
SDL_Rect back;
//SDL_Rect pos={0,0, 0, 0};
double accelerate ;  // g

SDL_Rect bkp={0,0,0,0};
SDL_bool isDick[3];
SDL_Rect DPos[3]={
        {1100,350,78,78},
        {1800,200,78,78},
        {2200,385,78,78}
};
SDL_Rect collect[3]={
        {10,10,50,50},
        {70,10,50,50},
        {130,10,50,50},


};
void addBlock()
{

    addQBlocks(150,100,50,50,10,1);
    addQBlocks(150,285,50,50,10,2);
    addQBlocks(650,180,50,50,10,3);
    addQBlocks(700,390,50,50,10,4);
    addPipeBlocks(200,285,5,0);
    addPipeBlocks(205,335,6,1);
    addPipeBlocks(205,385,7,2);
    addPipeBlocks(205,435,8,2);
    addQBlocks(300,100,50,50,10,9);
    addPipeBlocks(420,85,10,0);
    addPipeBlocks(425,135,11,1);
    addQBlocks(425,185,50,50,10,12);
    addQBlocks(475,185,50,50,10,13);
    addPipeBlocks(450,385,14,0);
    addPipeBlocks(455,435,15,1);
    for(int i=0;i<5;i++)
        addQBlocks(900+50*i,165,50,50,10,16+i);

    addPipeBlocks(870,335,21,0);
    addPipeBlocks(875,385,22,1);
    addPipeBlocks(875,435,23,2);

    addPipeBlocks(1350,85,24,0);
    addPipeBlocks(1355,135,25,1);
    addPipeBlocks(1355,185,26,2);
    addPipeBlocks(1355,235,27,2);
    addPipeBlocks(1355,285,28,2);
    addPipeBlocks(1355,335,29,2);
    addPipeBlocks(1355,385,30,2);
    addPipeBlocks(1355,435,31,2);
    for(int i=0;i<7;i++)
        addQBlocks(1600,i*50,50,50,10,32+i);
    for(int i=0;i<7;i++)
        addQBlocks(1950,135+i*50,50,50,10,39+i);
    addPipeBlocks(2050,235,46,0);
    addPipeBlocks(2055,285,47,1);
    addPipeBlocks(2055,335,48,2);
    addPipeBlocks(2055,385,49,2);
    addPipeBlocks(2055,435,50,2);

    addPipeBlocks(2450,335,51,0);
    addPipeBlocks(2455,385,52,1);
    addPipeBlocks(2455,435,53,2);
}
SDL_bool changeBlock()
{
    ChangeQblockPos(1,back);
    ChangeQblockPos(2,back);
    ChangeQblockPos(3,back);
    ChangeQblockPos(4,back);
    ChangePipePos(5,back);
    ChangePipePos(6,back);
    ChangePipePos(7,back);
    ChangePipePos(8,back);
    ChangeQblockPos(9,back);
    ChangePipePos(10,back);
    ChangePipePos(11,back);
    ChangeQblockPos(12,back);
    ChangeQblockPos(13,back);
    ChangePipePos(14,back);
    ChangePipePos(15,back);
    for(int i=0;i<5;i++)
        ChangeQblockPos(16+i,back);
    ChangePipePos(21,back);
    ChangePipePos(22,back);
    ChangePipePos(23,back);
    for(int i=0;i<8;i++)
        ChangePipePos(24+i,back);
    for(int i=0;i<14;i++)
        ChangeQblockPos(32+i,back);
    for(int i=0;i<8;i++)
        ChangePipePos(46+i,back);
}

SDL_bool backgroud()
{


    //SDL_Rect rec={801,512,53,53};
    bkp.w=logical_width;
    bkp.h=logical_height;
    SDL_RenderCopyEx(renderer, TFD, NULL, &bkp, 0, NULL, SDL_FLIP_NONE);
    SDL_Rect tmpbkp = bkp;
    tmpbkp.x += logical_width;
    SDL_RenderCopyEx(renderer, TFD, NULL, &tmpbkp, 0, NULL, SDL_FLIP_NONE);

}
int stage2()
{

    load_WAV("audios/kami.wav",SDL_TRUE);
    reset();
    SDL_PauseAudio(0);
    for(int i=0;i<3;i++)
    {
        isDick[i] = SDL_FALSE;
    }
    /*
     loadWAV
     */
    Yspeed=0;
    accelerate = 0.1;
    character.y = 100;
    character.x = 0;
    bkp.x=0;
    bkp.y=0;
    d[0].deg=0;
    back.x=0;
    back.y=0;
    back.h=0;
    back.w=0;

    addBlock();

    while (1)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                // SDL_CloseAudio();
                return SDL_FALSE;

            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                Yspeed=2;
                d[0].isDick=SDL_TRUE;
            }
        }



        Yspeed -= accelerate;
        character.y -= Yspeed;
        bkp.x = back.x%logical_width;
        if(character.x < (logical_width/2))
        {
            character.x +=1;
        }else{
            back.x -=1;
        }
        if(character.y<0 || character.y >logical_height-140)
        {
            stop_WAV();
            return die2();
        }
        //SDL_Log("%d",character.y);
        if(checkCollides(character,back))
        {
            stop_WAV();
            return die2();
        }
        SDL_RenderClear(renderer);
        backgroud();

        putQblock();
        putPipeBlocks();
        changeBlock();
       // SDL_RenderCopyEx(renderer, PipeTexture, &Pipe[0],&test, 0, NULL, SDL_FLIP_NONE);
        //SDL_RenderCopyEx(renderer, PipeTexture, &Pipe[1],&test2, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &character, d[0].deg, NULL, SDL_FLIP_NONE);
        if(d[0].isDick)
        {
            d[0].deg+=3;
        }
        if (d[0].deg>=360)
        {
            d[0].deg = 0;
            d[0].isDick = SDL_FALSE;
            d[0].RotateTime++;
        }
        for(int i=0;i<3;i++)
        {
            SDL_Rect tmp=DPos[i];
            tmp.x += back.x;
            tmp.y += back.y;
            if(!isDick[i])
                SDL_RenderCopyEx(renderer, d[i+1].Dtext, NULL, &tmp, 0, NULL, SDL_FLIP_NONE);
            else
                SDL_RenderCopyEx(renderer, d[i+1].Dtext, NULL, &collect[i], 0, NULL, SDL_FLIP_NONE);
            if(collideBlock(character,tmp))
            {
                isDick[i] = SDL_TRUE;

            }
        }
        if(isDick[0] && getObjectsPos(24,back).y<400)
        {
            for(int i=0;i<8;i++)
            {
                SDL_Rect tmp= {0,5,0,0};

                movePipePos(24+i,tmp);
            }
           // SDL_Log("%d",getObjectsPos(24,back).y);
        }
        if(back.x < -2200)
        {
            return SDL_TRUE;
        }
        SDL_RenderPresent(renderer); // 更新屏幕显示
        SDL_Delay(10);
    }
}
int stage2pass()
{
   // reset();
    double deg=0;
    while(back.x>-2600)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                stop_WAV();
                return SDL_FALSE;
            }
        }
        back.x -=1;
        SDL_RenderClear(renderer);
        backgroud();
        putQblock();
        putPipeBlocks();
        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &character, d[0].deg, NULL, SDL_FLIP_NONE);
        d[0].deg += 3;
        bkp.x  = back.x % logical_width;
        changeBlock();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    stop_WAV();
    freeQuestionblocks();
    freePipes();
    freeObjects();
    return SDL_TRUE;

}
int die2()
{
    double speed = -8;
    load_WAV("audios/dick_dies_2.wav",SDL_FALSE);
    SDL_PauseAudio(0);
   // reset();
    double deg=0;
    while(character.y<600)
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                stop_WAV();
                return SDL_FALSE;
            }
        }

        SDL_RenderClear(renderer);
        backgroud();
        putQblock();
        putPipeBlocks();
        //SDL_RenderCopyEx(renderer, Tbk, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, d[0].Dtext, NULL, &character, deg, NULL, SDL_FLIP_NONE);
        character.y+=speed;
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
    freeObjects();
    freeQuestionblocks();
    freePipes();
    stop_WAV();
    freeQuestionblocks();
    freePipes();
    freeObjects();
    return 2;
}