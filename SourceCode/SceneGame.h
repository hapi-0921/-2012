#pragma once
#include "SceneBase.h"
#include "player.h"

class SceneResult;

class SceneGame :public SceneBase
{
public:
    SceneGame(SceneManager* mgr, SceneBase* next) :SceneBase(mgr), nextScene(next) {}

    void Initialize();
    void Update(float delta_time);
    void Draw();
    void Finalize();


private:
    SceneBase* nextScene;

    Player player;


#ifdef _DEBUG
    void DrawImGui();  // ImGui描画用の関数（引数なし）
#endif
};
