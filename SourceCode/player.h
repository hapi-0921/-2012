#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Mapchip.h"

struct CursorPos
{
    int x;
    int y;
};

struct Button
{
    float x;
    float y;
    float width;
    float height;
    int index;
};

class Player
{
private:
    int cursorX;
    int cursorY;
    int GetcursorIndex;

    bool useKeyboard;

    Sprite* spr_Character;


public:
    Player();
    ~Player();

    bool IsHovered(Button button, float mouseX, float mouseY);

    bool prevMouseLeft;

    int GetCursorIndex();
    bool decided;
    bool IsDecided();

    bool MenuUpdate(int memuMax);//メニュー(titleやresultで使う用)
    bool GameUpdate(Map& mapchip);//ゲーム内で使う用

    void reset();

    bool GetSelecting();
    int GetSelectingRow();
    int GetSelectingCol();
    int GetCursorRow();
    int GetCursorCol();

    bool isKeyboardMode();

    CursorPos getCursorpos();

    Map mapchip;
};
#endif //PLAYER_H