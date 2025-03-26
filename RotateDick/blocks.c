//
// Created by shousake on 2024/12/10.
//
#include "blocks.h"
//#include "functions.h"
SDL_Texture *QblockTexture;
SDL_Texture *PipeTexture;
struct objects *Objects=NULL ;
SDL_Rect P[3]=
        {
                {0,0,110,50},
                {0,0,100,50},
                {0,0,100,50}
        };
SDL_Rect Qposition[4] =
        {
                {1,0,108,95},
                {110,0,108,95},
                {219,0,108,95},
                {328,0,108,95}
        };
SDL_Rect NullBlock={437,0,108,95};
struct NullBlock *Nblocks=NULL;
struct Questionblock *Qblocks=NULL;
struct pipeBlock *Pblocks=NULL;
SDL_Rect Pipe[3] = {
        {540,493,65,33},
        {544,526,57,24},
        {544,550,57,24}
};
SDL_bool initPipes()
{
    PipeTexture = get_BMPTexture("pic/back0.bmp");
    if(PipeTexture == NULL)
    {
        exit(1) ;
    }
    return SDL_TRUE;
}
SDL_bool initQblocks()
{

    QblockTexture= get_BMPTexture("pic/Qblocks.bmp");
    if (QblockTexture == NULL )
    {
        exit(1);
    }
    return SDL_TRUE;
}
SDL_bool putQblock() {
    struct Questionblock* current = Qblocks;
    while (current != NULL) {
        if (current->isUse) {
            SDL_Rect rec;
            rec.x = current->x;
            rec.y = current->y;
            rec.w = current->width;
            rec.h = current->height;
            SDL_RenderCopyEx(renderer, QblockTexture, &Qposition[current->num], &rec, 0, NULL, SDL_FLIP_NONE);

            if (current->count == current->frequency) {
                current->num++;
                if (current->num == 4)
                    current->num = 0;
                current->count = 0;
            } else {
                current->count++;
            }
        }
        current = current->next; // 移动到下一个节点
    }

    return SDL_TRUE;
}

SDL_bool addQBlocks(int x,int y,int width,int height,int frequency,int BlockID)
{
    struct Questionblock *i;
    i = Qblocks;
    struct Questionblock* prev = NULL;

    while(i != NULL)
    {
        if(i->BlockID == BlockID)
        {
            return SDL_FALSE;
        }
        i=i->next;
    }
    i = Qblocks;
    while(i != NULL && i->isUse)
    {

        prev = i;
        i = i->next;
    }
    if(i!=NULL)
    {
        i->x = x;
        i->y = y;
        i->width = width;
        i->height = height;
        i->frequency = frequency;
        i->BlockID = BlockID;
        i->num=0;
        i->count=0;
    }else{
        struct Questionblock* newBlock = (struct Questionblock*)malloc(sizeof(struct Questionblock));
        if (newBlock == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return SDL_FALSE;
        }
        newBlock->x = x;
        newBlock->y = y;
        newBlock->width = width;
        newBlock->height = height;
        newBlock->isUse = SDL_TRUE;
        newBlock->frequency = frequency;
        newBlock->BlockID = BlockID;
        newBlock->next = NULL;
        newBlock->num=0;
        newBlock->count=0;
        if (prev != NULL) {
            prev->next = newBlock;
        } else {
            Qblocks = newBlock;  // 如果链表为空，更新头节点
        }
    }
    SDL_Rect tmp;
    tmp.x=x;
    tmp.y=y;
    tmp.h = height;
    tmp.w = width;
    addObjects(BlockID,tmp);
    return SDL_TRUE;
}
void freeQuestionblocks() {
    struct Questionblock* current = Qblocks;


    while (current != NULL) {
        struct Questionblock *temp = current;
        current = current->next;  // 保存下一个节点
        free(temp);  // 释放当前节点的内存
        temp = NULL;
    }
    Qblocks = NULL; // 确保头节点被设置为NULL，表示链表已清空
}
SDL_bool DeleteQblock(int BlockID) {
    struct Questionblock* current = Qblocks;
    struct Questionblock* prev = NULL;

    while (current != NULL) {
        if (current->BlockID == BlockID) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                Qblocks = current->next; // 如果删除的是头节点
            }
            free(current);
            current = NULL;
            return SDL_TRUE;
        }
        prev = current;
        current = current->next;
    }

    return SDL_FALSE; // 未找到指定的BlockID
}
SDL_bool ChangeQblockPos(int BlockID,SDL_Rect change) {
    struct Questionblock* current = Qblocks;
   // SDL_Rect tmp=getObjectsPos(BlockID);
    SDL_Rect tmp=getObjectsPos(BlockID,change);
    while (current != NULL) {
        if (current->BlockID == BlockID) {
            current->x = tmp.x;
            current->y = tmp.y;
            return SDL_TRUE;
        }

        current = current->next;
    }

    return SDL_FALSE; // 未找到指定的BlockID
}
SDL_bool addNullBlock(int x,int y,int width,int height,int BlockID)
{
    struct NullBlock *i;
    i = Nblocks;
    struct NullBlock* prev = NULL;
    while(i != NULL)
    {
        if(i->BlockID == BlockID)
        {
            return SDL_FALSE;
        }
        prev = i;
        i = i->next;
    }
    // i = Nblocks;
    if(i!=NULL)
    {
        i->x = x;
        i->y = y;
        i->width = width;
        i->height = height;

        i->BlockID = BlockID;

    }else{
        struct NullBlock* newBlock = (struct NullBlock*)malloc(sizeof(struct NullBlock));
        if (newBlock == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return SDL_FALSE;
        }
        newBlock->x = x;
        newBlock->y = y;
        newBlock->width = width;
        newBlock->height = height;


        newBlock->BlockID = BlockID;
        newBlock->next = NULL;
        if (prev != NULL) {
            prev->next = newBlock;
        } else {
            Nblocks = newBlock;  // 如果链表为空，更新头节点
        }
    }
    SDL_Rect tmp;
    tmp.x=x;
    tmp.y=y;
    tmp.h = height;
    tmp.w = width;
    addObjects(BlockID,tmp);
    return SDL_TRUE;

}
SDL_bool putNullBlocks()
{
    struct NullBlock* current = Nblocks;
    while (current != NULL) {

        SDL_Rect rec;
        rec.x = current->x;
        rec.y = current->y;
        rec.w = current->width;
        rec.h = current->height;
        SDL_RenderCopyEx(renderer, QblockTexture, &NullBlock, &rec, 0, NULL, SDL_FLIP_NONE);



        current = current->next; // 移动到下一个节点
    }

    return SDL_TRUE;
}
void freeNullblocks() {
    struct NullBlock* current = Nblocks;


    while (current != NULL) {
        struct NullBlock *temp = current;
        current = current->next;  // 保存下一个节点
        free(temp);  // 释放当前节点的内存
        temp = NULL;
    }
    Nblocks = NULL; // 确保头节点被设置为NULL，表示链表已清空
}
SDL_bool collideBlock(SDL_Rect character, SDL_Rect object) {
    // 检查角色矩形是否和物体矩形相交
    if (character.x + character.w > object.x &&
        character.x < object.x + object.w &&
        character.y + character.h > object.y &&
        character.y < object.y + object.h) {
        return SDL_TRUE; // 碰撞发生
    }
    return SDL_FALSE; // 没有碰撞
}


SDL_bool addPipeBlocks(int x,int y,int BlockID, int pattern)
{
    struct pipeBlock *i;
    i = Pblocks;
    struct pipeBlock* prev = NULL;
    while(i != NULL)
    {
        if(i->BlockID == BlockID)
        {
            return SDL_FALSE;
        }
        prev = i;
        i = i->next;
    }

    // i = Nblocks;
    if(i!=NULL)
    {
        i->x = x;
        i->y = y;

        i->width = P[pattern].w;
        i->height = P[pattern].h;


        //57.24
        i->pattern = pattern;
        i->BlockID = BlockID;
    }else {
        struct pipeBlock *newBlock = (struct pipeBlock *) malloc(sizeof(struct pipeBlock));
        if (newBlock == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return SDL_FALSE;
        }
        newBlock->x = x;
        newBlock->y = y;
        newBlock->pattern =pattern;
        newBlock->width = P[pattern].w;
        newBlock->height = P[pattern].h;
        newBlock->BlockID = BlockID;
        newBlock->next = NULL;
        if (prev != NULL) {
            prev->next = newBlock;
        } else {
            Pblocks = newBlock;  // 如果链表为空，更新头节点
        }
    }
    SDL_Rect tmp;
    tmp.x=x;
    tmp.y=y;
    tmp.h = P[pattern].h;
    tmp.w = P[pattern].w;
    addObjects(BlockID,tmp);
    return  SDL_TRUE;
}
SDL_bool putPipeBlocks()
{
    struct pipeBlock* current = Pblocks;
    while (current != NULL) {

        SDL_Rect rec;
        rec.x = current->x;
        rec.y = current->y;
        rec.w = current->width;
        rec.h = current->height;

        SDL_RenderCopyEx(renderer, PipeTexture, &Pipe[current->pattern], &rec, 0, NULL, SDL_FLIP_NONE);



        current = current->next; // 移动到下一个节点
    }

    return SDL_TRUE;
}
SDL_bool ChangePipePos(int BlockID,SDL_Rect change) {
    struct pipeBlock* current = Pblocks;
   // struct pipeBlock* prev = NULL;

    SDL_Rect tmp=getObjectsPos(BlockID,change);
    while (current != NULL) {
        if (current->BlockID == BlockID) {
            current->x = tmp.x;
            current->y = tmp.y;
            return SDL_TRUE;
        }
       // prev = current;
        current = current->next;
    }

    return SDL_FALSE; // 未找到指定的BlockID
}
SDL_bool movePipePos(int BlockID,SDL_Rect move) {
    struct objects* current = Objects;
    // struct pipeBlock* prev = NULL;

    while (current != NULL) {
        if (current->ID == BlockID) {
            current->rect.x += move.x;
            current->rect.y += move.y;
            //SDL_Log("%d", current->y);
            return SDL_TRUE;
        }
        // prev = current;
        current = current->next;
    }

    return SDL_FALSE; // 未找到指定的BlockID
}
SDL_bool addObjects(int ID, SDL_Rect newRect)
{
    // 创建新的节点
    struct objects *newObject = (struct objects*)malloc(sizeof(struct objects));
    if (newObject == NULL) {
        // 如果内存分配失败，返回 SDL_FALSE
        return SDL_FALSE;
    }

    // 设置新节点的属性
    newObject->ID = ID;
    newObject->rect = newRect;
    newObject->next = NULL;

    // 如果链表为空，直接将新节点设置为链表头
    if (Objects == NULL) {
        Objects = newObject;
    } else {
        // 否则，遍历链表找到最后一个节点并插入新节点
        struct objects *current = Objects;
        while (current->next != NULL) {
            if(current->ID == newObject->ID)
            {
                return SDL_FALSE;
            }
            current = current->next;
        }
        current->next = newObject;
    }

    // 返回成功
    return SDL_TRUE;
}
SDL_bool deleteObject(int ID)
{
    // 如果链表为空，直接返回
    if (Objects == NULL) {
        return SDL_FALSE;
    }

    // 如果头节点就是要删除的对象
    if (Objects->ID == ID) {
        struct objects *temp = Objects;
        Objects = Objects->next;  // 移动链表头
        free(temp);  // 释放被删除节点的内存
        return SDL_TRUE;
    }

    // 遍历链表找到匹配的节点
    struct objects *current = Objects;
    while (current->next != NULL) {
        if (current->next->ID == ID) {
            struct objects *temp = current->next;
            current->next = current->next->next;  // 移除节点
            free(temp);  // 释放节点的内存
            temp = NULL;
            return SDL_TRUE;
        }
        current = current->next;
    }

    // 如果没有找到匹配的节点
    return SDL_FALSE;
}
SDL_bool checkCollides(SDL_Rect character,SDL_Rect change)
{
   // SDL_Log("%f",character.y);
    struct objects* current = Objects;
    //struct objects *prev = NULL;
    while(current != NULL)
    {
        SDL_Rect tmp = getObjectsPos(current->ID,change);

    //    SDL_Log("%d %d %d %d %d %d %d %d\n",character.x,character.y,character.w,character.h,tmp.x,tmp.y,tmp.w,tmp.h);
        if(collideBlock(character,tmp))
        {
            return SDL_TRUE;
        }
       // prev = current;
        current = current->next;
    }
    return  SDL_FALSE;

}
SDL_Rect getObjectsPos(int ID,SDL_Rect change)
{
    struct objects *current = Objects;

    // 遍历链表，查找匹配的ID
    while (current != NULL) {
        if (current->ID == ID) {
            SDL_Rect tmp = current->rect;
            tmp.x+=change.x;
            tmp.y+=change.y;
            return tmp;  // 找到匹配的ID，返回对应的rect
        }
        current = current->next;
    }

    // 如果没有找到，返回一个默认的SDL_Rect（例如，坐标和大小均为0）
    SDL_Rect defaultRect = {0, 0, 0, 0};
    return defaultRect;
}
void freeObjects()
{
    struct objects *current = Objects;
    while (current != NULL) {
        struct objects *temp = current;
        current = current->next;  // 保存下一个节点
        free(temp);  // 释放当前节点的内存
        temp = NULL;
    }
    Objects = NULL;  // 将链表头设置为 NULL
}
void freePipes()
{
    struct pipeBlock *current = Pblocks;

    while (current != NULL) {
        struct pipeBlock *temp = current;
        current = current->next;  // 保存下一个节点
        free(temp);  // 释放当前节点的内存
        temp = NULL;
    }
    Pblocks = NULL;  // 将链表头设置为 NULL
}

