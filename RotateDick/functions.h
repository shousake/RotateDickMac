#ifndef ROTATEDICK_FUNCTIONS_H
#define ROTATEDICK_FUNCTIONS_H

#include<SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <libgen.h>
#include<math.h>
SDL_Renderer* renderer;
SDL_Texture *TRD;
SDL_Texture *Tbk;
SDL_Window* window;
int logical_width = 970;
int logical_height = 545;
char cwd[1024];
char pdir[1024];
typedef struct {
    Uint8* start; // 音频数据起始位置
    Uint8* pos;   // 当前音频数据位置
    Uint32 length; // 当前剩余长度
    Uint32 total_length; // 音频数据总长度
} AudioData;

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
void audio_callback(void* userdata, Uint8* stream, int len);
void end();
SDL_AudioSpec wav_spec;
Uint8* wav_buffer;
Uint32 wav_length;
AudioData audio;
void audio_callback_once(void* userdata, Uint8* stream, int len) {
    AudioData* audio = (AudioData*)userdata;



    len = (len > audio->length ? audio->length : len);
    SDL_memcpy(stream, audio->pos, len);

    audio->pos += len;
    audio->length -= len;
}
void audio_callback(void* userdata, Uint8* stream, int len) {
    AudioData* audio = (AudioData*)userdata;

    if (audio->length == 0) {
        // 如果音频播放完毕，重新开始播放
        audio->pos = audio->start;
        audio->length = audio->total_length;
    }

    len = (len > audio->length ? audio->length : len);
    SDL_memcpy(stream, audio->pos, len);

    audio->pos += len;
    audio->length -= len;
}
void end()
{
    SDL_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


#endif //ROTATEDICK_FUNCTIONS_H