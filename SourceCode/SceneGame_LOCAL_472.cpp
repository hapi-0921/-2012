#include "SceneGame.h"
#include "SceneManager.h"
#include"SceneResult.h"
#include "SceneTitle.h"
#include "tori.h"

Tori* tori = new Tori;

void SceneGame::Initialize()
{
	tori->Initialize();
}

void SceneGame::Finalize()
{
	tori->Finalize();
}

void SceneGame::Update()
{

    //エンターでリザルトへ
    if (TRG(0) & PAD_START)
    {
        SceneResult* result = new SceneResult(manager);
        manager->ChangeScene(result);
        return;
    }

	tori->Update();
}

void SceneGame::Draw()
{
    GameLib::clear(0.09f, 0.09f, 0.43f);
	tori->Draw();
#ifdef _DEBUG
    DrawImGui();  // ImGui描画（引数なし、シンプル！）
#endif

}

#ifdef _DEBUG
void SceneGame::DrawImGui()
{
    ImGui::Begin("Debug Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    // FPS表示
    ImGui::Text("FPS: %.1f (%.2f ms)",
        ImGui::GetIO().Framerate,
        1000.0f / ImGui::GetIO().Framerate);
    ImGui::Separator();




    // シーン遷移ボタン
    ImGui::Text("Scene Transition:");
    if (ImGui::Button("Go to Title", ImVec2(150, 0)))
    {
        manager->ChangeScene(new SceneTitle(manager, nullptr));
    }
    ImGui::SameLine();
    if (ImGui::Button("Go to Result", ImVec2(150, 0)))
    {
        manager->ChangeScene(new SceneResult(manager, nullptr));
    }

    ImGui::Separator();

    ImGui::End();

}
#endif
