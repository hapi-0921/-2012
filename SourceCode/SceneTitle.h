#pragma once
#include "SceneBase.h"
#include "player.h"
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

  
private:
    SceneBase* nextScenePtr;

    Player player;

    int cursorIndex;


#ifdef _DEBUG
    void DrawImGui();
#endif
};
