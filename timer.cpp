#include"DxLib.h"
#include"timer.h"
#include"common.h"
#include"proceedScene.h"
#include"sandClock.h"

Timer::Timer()
{
    frameTimer_     = standardNumber;                   
    secondsTimer_   = oneminute;                              
    startTime_      = GetNowCount();
    timeLimit_      = oneminute;
}

Timer::~Timer()
{
}

//制限時間
void Timer::limit_(ProceedScene* proceedScene, SandClock* sandClock)
{
    frameTimer_     = GetNowCount() - startTime_;           //1秒カウントする
    secondsTimer_   = timeLimit_ - (frameTimer_ / 1000);    //秒数タイマーをへらしていく
    secondsTimer_   += proceedScene->GetaddTimer_();        //ポーズ中の経過時間を足す
    if (secondsTimer_ > oneminute)                          //ポーズ中の時間が60秒を超えそうになったら60にもどす           
    {
        secondsTimer_ = oneminute;
    }

    //制限時間を回復
    heal_(sandClock);
}

//リセット
void Timer::reset_()
{
    frameTimer_     = standardNumber;
    secondsTimer_   = oneminute;
    timeLimit_      = oneminute;
    start_();
}

//スタート
void Timer::start_()
{
    startTime_ = GetNowCount();
}

//回復
void Timer::heal_(SandClock* sandClock)
{
    //砂時計をとったときに制限時間を回復する
    if (sandClock->GetisAddTimer_())
    {
        timeLimit_ += healNumber;
        sandClock->cannotAddTimer_();
    }
}