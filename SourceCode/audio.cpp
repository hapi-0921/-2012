#include "audio.h"
#include "../GameLib/game_lib.h"

void audio_init()
{
    //ƒ^ƒCƒgƒ‹
   /* music::load(0, L"./Data/Musics/music1long.wav");*/

    music::load(1, L"./Data/Sound/block_click1.wav");

    music::load(2, L"./Data/Sound/block_slide.wav");

    music::load(3, L"./Data/Sound/block_click3.wav");



}

void audio_deinit()
{

}