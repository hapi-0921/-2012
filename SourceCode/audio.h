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
#define XWB_GAME 1;
#define XWB_BOMB 2;
#define XWB_SWITCH 3;
#define XWB_COIN 4;

// 関数のプロトタイプ宣言
void audio_init();
void audio_deinit();

#endif//AUDIO_H
