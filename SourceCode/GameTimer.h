#pragma once
#include <chrono>

class GameTimer
{
private:
    // 高精度な時計の型定義（長いので短縮）
    using Clock = std::chrono::high_resolution_clock;
    // 時間の瞬間の型
    using TimePoint = std::chrono::time_point<Clock>;

    // 前回の時間を記録しておく変数
    TimePoint m_lastTime;

private:
    // コンストラクタ（作成時に現在時刻を記録）
    GameTimer()
    {
        m_lastTime = Clock::now();
    }

public:
    // コピー禁止
    GameTimer(const GameTimer&) = delete;
    void operator=(const GameTimer&) = delete;

    // インスタンス取得
    static GameTimer& GetInstance()
    {
        static GameTimer instance_;
        return instance_;
    }

    // 前回の呼び出しからの経過時間（秒）を返して、基準時間を更新する関数
    float Tick() {
        // 現在時刻を取得
        TimePoint currentTime = Clock::now();

        // 経過時間を計算（現在 - 前回）
        std::chrono::duration<float> deltaTime = currentTime - m_lastTime;

        // 基準時間を現在に更新（次回の計算のため）
        m_lastTime = currentTime;

        // float型の秒数を返す（例: 0.01666...）
        return deltaTime.count();
    }

    // 時間をリセットする（ゲームのリスタート時などに使う）
    void Reset() {
        m_lastTime = Clock::now();
    }
};

