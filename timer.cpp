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

//��������
void Timer::limit_(ProceedScene* proceedScene, SandClock* sandClock)
{
    frameTimer_     = GetNowCount() - startTime_;           //1�b�J�E���g����
    secondsTimer_   = timeLimit_ - (frameTimer_ / 1000);    //�b���^�C�}�[���ւ炵�Ă���
    secondsTimer_   += proceedScene->GetaddTimer_();        //�|�[�Y���̌o�ߎ��Ԃ𑫂�
    if (secondsTimer_ > oneminute)                          //�|�[�Y���̎��Ԃ�60�b�𒴂������ɂȂ�����60�ɂ��ǂ�           
    {
        secondsTimer_ = oneminute;
    }

    //�������Ԃ���
    heal_(sandClock);
}

//���Z�b�g
void Timer::reset_()
{
    frameTimer_     = standardNumber;
    secondsTimer_   = oneminute;
    timeLimit_      = oneminute;
    start_();
}

//�X�^�[�g
void Timer::start_()
{
    startTime_ = GetNowCount();
}

//��
void Timer::heal_(SandClock* sandClock)
{
    //�����v���Ƃ����Ƃ��ɐ������Ԃ��񕜂���
    if (sandClock->GetisAddTimer_())
    {
        timeLimit_ += healNumber;
        sandClock->cannotAddTimer_();
    }
}