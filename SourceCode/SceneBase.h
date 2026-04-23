#pragma once
#include"../GameLib/game_lib.h"

class SceneManager;

class SceneBase
{
protected:
    SceneManager* manager = nullptr;

public:
    SceneBase(SceneManager* mgr) :manager(mgr) {}
    virtual ~SceneBase() {}

    virtual void Initialize() {}
    virtual void Update(float delta_time) {}
    virtual void Draw() {}
    virtual void Finalize() {}
};
