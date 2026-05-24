#pragma once
#include "SceneBase.h"
#include "player.h"
#include "Character.h"
class SceneGame;



class SceneTitle :public SceneBase
{
public:
    SceneTitle(SceneManager* mgr, SceneBase* next = nullptr)
        :SceneBase(mgr), nextScenePtr(next) {
    }

    void Initialize()override;
    void Finalize()override;
    void Update(float delta_time)override;
    void Draw()override;
    void Drawbutton(Button button);

    //雲
    struct Cloud
    {
        float x;
        float y;
        float speed;
    };

    Cloud clouds[6];



private:
    SceneBase* nextScenePtr;

    Player player;

    Character character;

    int cursorIndex;

   


#ifdef _DEBUG
    void DrawImGui();
#endif
};
