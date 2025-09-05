#pragma once

class ProceedScene;
class SandClock;

class Timer
{
public:
	Timer();
	~Timer();

	void limit_(ProceedScene* proceedScene, SandClock* sandClock);	//制限時間
	void reset_();													//リセット
	void start_();													//スタート

	int GetframeTimer_()const { return frameTimer_; }
	int GetsecondsTimer_()const { return secondsTimer_; }
	int GetstartTime_()const { return startTime_; }

private:
	void heal_(SandClock* sandClock);	//回復

	int frameTimer_;					//タイマー(フレーム)
	int secondsTimer_;					//タイマー(秒)
	int startTime_;						//計測開示時間
	int timeLimit_;						//タイムリミット

	const int healNumber = 10;			//回復量
};