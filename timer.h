#pragma once

class ProceedScene;
class SandClock;

class Timer
{
public:
	Timer();
	~Timer();

	void limit_(ProceedScene* proceedScene, SandClock* sandClock);	//��������
	void reset_();													//���Z�b�g
	void start_();													//�X�^�[�g

	int GetframeTimer_()const { return frameTimer_; }
	int GetsecondsTimer_()const { return secondsTimer_; }
	int GetstartTime_()const { return startTime_; }

private:
	void heal_(SandClock* sandClock);	//��

	int frameTimer_;					//�^�C�}�[(�t���[��)
	int secondsTimer_;					//�^�C�}�[(�b)
	int startTime_;						//�v���J������
	int timeLimit_;						//�^�C�����~�b�g

	const int healNumber = 10;			//�񕜗�
};