#pragma once
#include<memory>
#include"SceneBase.h"
//******************************************************************************
//
//      SceneManager - シーン管理クラス
//
//      役割：ゲーム内のシーン（タイトル、ゲーム、リザルトなど）を
//            切り替えて管理する司令塔
//
//******************************************************************************

class SceneManager
{
private:
    SceneBase* currentScene = nullptr;  //現在実行中のシーン
    SceneBase* nextScene = nullptr;     //次に切り替わるシーン（予約用）

public:
    //------------------------------------------------------------------------------
   //  コンストラクタ
   //  説明：SceneManagerを作成し、シーンポインタをnullptrで初期化
   //------------------------------------------------------------------------------
    SceneManager() :currentScene(nullptr), nextScene(nullptr) {}

    //------------------------------------------------------------------------------
 //  デストラクタ
 //  説明：SceneManagerが破棄される時に呼ばれる
 //        現在のシーンと予約中のシーンのメモリを解放する
 //------------------------------------------------------------------------------
    ~SceneManager()
    {
        //限歳のシーンが存在する場合
        if (currentScene)
        {
            currentScene->Finalize();   //シーンの終了処理を呼ぶ
            delete currentScene;        //メモリを解放
            currentScene = nullptr;     //ポインタをnullptrにする

            //次のシーンが予約されている場合
            if (nextScene)

                delete nextScene;           //メモリを解放
            nextScene = nullptr;            //ポインタをnullptrにする
        }

        if (nextScene)
        {
            delete nextScene;
        }

    }

    //------------------------------------------------------------------------------
    //  ChangeScene - シーン遷移を予約
    //  引数：newScene - 次に切り替えたいシーンのポインタ（newで作成）
    //  説明：次のUpdate()で実際にシーンが切り替わる
    //        例：manager->ChangeScene(new SceneGame(manager, nullptr));
    //------------------------------------------------------------------------------
    void ChangeScene(SceneBase* newScene)
    {
        //すでに別のシーンが予約されている場合は、古い予約を削除
        if (nextScene)
        {
            delete nextScene;
            nextScene = nullptr;
        }
        //新しいシーンを予約
        nextScene = newScene;

    }

    //------------------------------------------------------------------------------
    //  Update - シーンの更新処理
    //  説明：1. 予約されたシーンがあれば切り替える
    //        2. 現在のシーンのUpdate()を呼ぶ
    //  注意：この順番により、Draw中にシーンが切り替わるのを防ぐ
    //------------------------------------------------------------------------------
    void Update(float delta_time)
    {
        //次のシーンが予約されている場合、シーンを切り替える
        if (nextScene)
        {
            //現在のシーンは存在する場合は終了処理
            if (currentScene)
            {
                currentScene->Finalize();   //シーンの終了処理
                delete currentScene;        //古いシーンのメモリを解放
            }

            //シーンを切り替える
            currentScene = nextScene;       //予約していたシーンを現在のシーンにする
            nextScene = nullptr;            //予約をクリア

            //新しいシーンの初期化処理を呼ぶ
            if (currentScene)
            {
                currentScene->Initialize();
            }
        }

        //現在のシーンの初期化処理を呼ぶ
        if (currentScene)
        {
            currentScene->Update(delta_time);
        }
    }

    //------------------------------------------------------------------------------
    //  Draw - シーンの描画処理
    //  説明：現在のシーンのDraw()を呼ぶだけ
    //------------------------------------------------------------------------------
    void Draw()
    {
        if (currentScene)
        {
            currentScene->Draw();
        }
    }
};
