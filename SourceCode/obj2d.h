#pragma once
//------< 構造体 >--------------------------------------------------------------
struct OBJ2D
{
    int                 timer;      // タイマー

    char                pad[2];     // パディング（隙間）

    VECTOR2             pos;        // 位置
    VECTOR2             scale;      // スケール
    VECTOR2             texPos;     // 画像位置
    VECTOR2             texSize;    // 画像サイズ
    VECTOR2             pivot;      // 基準点
    VECTOR4             color;      // 色

    int                 act;        // プレイヤーの行動遷移用
    int                 anime;      // アニメが現在何コマ目か
    int                 animeTimer; // アニメ用タイマー
    int                 moveAlg;

    float width;
    float height;

    GameLib::Sprite* spr;
    int              state;

    float radius;
    VECTOR2 offset;
};

//------< 関数 >----------------------------------------------------------------
OBJ2D* searchSet0(OBJ2D arr[], int dataNum, int moveAlg, VECTOR2 pos);
