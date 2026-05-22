#include "audio.h"
#include "../GameLib/game_lib.h"

void audio_init()
{
    //BGM
    //タイトル
    music::load(0, L"./Data/Musics/music1long.wav");
    //ゲーム中
    music::load(6, L"./Data/Musics/music3long.wav");
    //リザルト
    music::load(9, L"./Data/Musics/music2long.wav");


    //SOUND
    //ボタン押したとき
    music::load(1, L"./Data/Sound/block_click1.wav");
    //ボタンを動かしたとき
    music::load(2, L"./Data/Sound/block_slide.wav");
    //ボタン押したとき
    music::load(3, L"./Data/Sound/block_click3.wav");
    //ボタン押したとき
    music::load(4, L"./Data/Sound/block_click2.wav");
    //本めくる、開くとき
    music::load(5, L"./Data/Sound/openbook.wav");
    //車に当たったとき
    music::load(7, L"./Data/Sound/kawaii3.wav");
    //クラクション
    music::load(8, L"./Data/Sound/clactionW.wav");
    //ゲームオーバー
    music::load(10, L"./Data/Sound/GAMEOVER.wav");
    //ゲームクリア
    music::load(11, L"./Data/Sound/GAMEOVER.wav");







}

void audio_deinit()
{

}