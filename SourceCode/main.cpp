#include "..\GameLib\game_lib.h"
#include"SceneManager.h"
#include "SceneTitle.h"
#include "GameTimer.h"

int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    //ゲームライブラリの初期設定
    GameLib::init(L"チーム制作", 1920, 1080, true);

#ifdef _DEBUG
    //ImGui初期化
    GameLib::imgui::init();
#endif //DEBUG

    {

        SceneManager manager;

        //最初のシーンをnewで作成してChangeScene
        manager.ChangeScene(new SceneTitle(&manager, nullptr));

        while (GameLib::gameLoop())
        {
            GameLib::clear(0, 0, 0);

#ifdef _DEBUG
            // ImGuiフレーム開始
            GameLib::imgui::newFrame();
#endif

            float deltaTime = GameTimer::GetInstance().Tick();
            if (deltaTime > 0.1f) deltaTime = 0.1f;

            input::update();
            music::update();
            manager.Update(deltaTime);
            manager.Draw();


#ifdef _DEBUG
            // ImGui描画
            GameLib::imgui::render();
#endif
            //debug::display(1.0f, 0.4f, 0.6f, 1, 1);


            GameLib::present(1, 0);
        }

    }

#ifdef _DEBUG
    // ImGui終了処理
    GameLib::imgui::uninit();
#endif

    GameLib::uninit();
    return 0;
}
