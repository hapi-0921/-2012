
#include "Number.h"
#include "../GameLib/game_lib.h"






Sprite* sprNumber[10];

void NumberInitialize()
{
    for (int i = 0; i < 10; i++)
    {
        std::wstring path =
            L"./Data/Images/" + std::to_wstring(i) + L".png";

        sprNumber[i] = sprite_load(path.c_str());
    }
}

void NumberFinalize()
{
    for (int i = 0; i < 10; i++)
    {
        safe_delete(sprNumber[i]);
    }
}

void DrawNumber(int x, int y, int number)
{
    int digits[3];
    int digitCount = 0;

    if (number == 0)
    {
        digits[0] = 0;
        digitCount = 1;
    }
    else
    {
        while (number > 0 && digitCount < 3)
        {
            digits[digitCount++] = number % 10;
            number /= 10;
        }
    }

    int offsetX = 0;

    for (int i = 0; i < digitCount; i++)
    {
        int d = digits[i];

        sprite_render(sprNumber[d],
            x - offsetX,
            y,
            0.5f,
            0.5f);

        offsetX += 64;
    }
}
void DrawRisultNumber(int x, int y, int number)
{
    int digits[3];
    int digitCount = 0;

    if (number == 0)
    {
        digits[0] = 0;
        digitCount = 1;
    }
    else
    {
        while (number > 0 && digitCount < 3)
        {
            digits[digitCount++] = number % 10;
            number /= 10;
        }
    }

    int offsetX = 0;

    for (int i = 0; i < digitCount; i++)
    {
        int d = digits[i];

        sprite_render(sprNumber[d],
            x - offsetX,
            y,
            1.0f,
            1.0f);

        offsetX += 130;
    }
}