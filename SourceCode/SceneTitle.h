#pragma once
#include "SceneBase.h"

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

  
private:
    SceneBase* nextScenePtr;
#ifdef _DEBUG
    void DrawImGui();
#endif
};
