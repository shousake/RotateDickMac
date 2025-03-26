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
extern SDL_Renderer* renderer;
extern SDL_Texture *TRD;
extern SDL_Texture *Tbk;
extern SDL_Window* window;
extern int logical_width ;
extern int logical_height ;
extern SDL_Texture* TFD;
extern char cwd[1024];
extern char pdir[1024];
typedef struct {
    Uint8* start; // 音频数据起始位置
    Uint8* pos;   // 当前音频数据位置
    Uint32 length; // 当前剩余长度
    Uint32 total_length; // 音频数据总长度
    SDL_bool loop; // 是否循环播放
    SDL_bool play; // 是否正在播放
} AudioData;
typedef struct
{
    SDL_AudioSpec wav_spec;
    Uint8* wav_buffer;
    Uint32 wav_length;
} Audio_Info;
struct Dick
{
    double deg;
    SDL_Surface *orDick;
    SDL_bool isDick;
    SDL_Texture *Dtext;
    SDL_Rect DPos;
    int RotateTime;
};
extern struct Dick d[6];
extern int rnum;
void audio_callback(void* userdata, Uint8* stream, int len);
void audio_callback_once(void* userdata, Uint8* stream, int len);
void mix_audio_callback(void* userdata, Uint8* stream, int len);
Uint8* convert_audio_format(SDL_AudioSpec* src_spec, Uint8* src_buffer, Uint32 src_length, SDL_AudioSpec* dst_spec, Uint32* dst_length);
void end();
SDL_Texture* get_BMPTexture(char *file);
void flipHorizontal(SDL_Surface* surface);
SDL_bool load_WAV(char *file,SDL_bool isRepeat);
void playWAV(char *file);
SDL_Texture* get_reserveBMPTexture(char *file);
SDL_Surface* get_BMPSerface(char *file);
SDL_bool isPos(int x, int y, int h, int w,SDL_Event event);
SDL_bool stop_WAV();
extern SDL_AudioSpec wav_spec;
extern Uint8* wav_buffer;
extern Uint32 wav_length;
extern AudioData audio;
extern AudioData audio_data[5];
extern Audio_Info audio_info[5];
#endif //ROTATEDICK_FUNCTIONS_H