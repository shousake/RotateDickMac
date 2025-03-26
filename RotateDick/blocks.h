//
// Created by shousake on 2024/7/13.
//

#ifndef ROTATEDICK_BLOCKS_H
#define ROTATEDICK_BLOCKS_H
#include "functions.h"

extern SDL_Texture *QblockTexture;
extern SDL_Texture *PipeTexture;
extern SDL_Rect Qposition[4] ;
extern SDL_Rect NullBlock;
struct Questionblock
{
    int num;
    int count;
    int x;
    int y;
    int width;
    int height;
    int frequency;
    SDL_bool isUse;
    int BlockID;
    struct Questionblock *next;
};
struct NullBlock
{
    int x;
    int y;
    int width;
    int height;
    int BlockID;
    struct NullBlock *next;
};
struct pipeBlock
{
    int x;
    int y;
    int width;
    int height;
    int BlockID;
    int pattern;
    struct pipeBlock *next;
};

struct objects
{
    SDL_Rect rect;
    int ID;
    struct objects *next;
};
//extern struct NullBlock *Nblocks;
//extern struct Questionblock *Qblocks;
//extern struct pipeBlock *Pblocks;
//extern struct objects *Objects;
//extern SDL_Rect Pipe[3];

SDL_bool initPipes();
SDL_bool initQblocks();
SDL_bool putQblock();
SDL_bool addQBlocks(int x,int y,int width,int height,int frequency,int BlockID);
void freeQuestionblocks();
SDL_bool DeleteQblock(int BlockID);

SDL_bool ChangeQblockPos(int BlockID,SDL_Rect change);
SDL_bool addNullBlock(int x,int y,int width,int height,int BlockID);
SDL_bool putNullBlocks();
SDL_bool collideBlock(SDL_Rect character,SDL_Rect object);
SDL_bool addPipeBlocks(int x,int y,int BlockID, int pattern);
SDL_bool putPipeBlocks();
SDL_bool ChangePipePos(int BlockID,SDL_Rect change);
SDL_bool movePipePos(int BlockID,SDL_Rect move);
SDL_bool checkCollides(SDL_Rect character,SDL_Rect change);
void freeObjects();
void freePipes();
SDL_bool deleteObject(int ID);
void freeNullblocks();
SDL_bool addObjects(int ID, SDL_Rect newRect);
SDL_Rect getObjectsPos(int ID,SDL_Rect change);
#endif //ROTATEDICK_BLOCKS_H
