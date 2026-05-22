#pragma once
#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

// 定数の定義
#define XWB_TITLE 0;
#define XWB_CLICK1 1;
#define XWB_SLIDE 2;
#define XWB_CLICK2 3;
#define XWB_CLICK3 4;
#define XWB_BOOK 5;
#define XWB_GAME 6;
#define XWB_ACTION 7;
#define XWB_CRACTION 8;
#define XWB_RESULT 9;
#define XWB_GAMEOVER 10;
#define XWB_GAMECREAR 11;





// 関数のプロトタイプ宣言
void audio_init();
void audio_deinit();

#endif//AUDIO_H
