#include"DxLib.h"
#include"common.h"
#include"transition.h"

//�R���X�g���N�^
Transition::Transition()
{
	transitionCount_	= standardNumber;
	canPlayTransition_	= true;
}

//�f�X�g���N�^
Transition::~Transition()
{
    DeleteGraph(handle_);
}

//������
void Transition::Init()
{
    handle_ = LoadGraph("video/last.mp4");
    SeekMovieToGraph(handle_, standardNumber);

    transitionCount_ = standardNumber;
    canPlayTransition_ = true;

    /*leftFlipHandle_ = LoadGraph("video/flipleft1.mp3");
    rightFlipHandle_ = LoadGraph("video/flipright1.mp3");
    leftLongFlipHandle_ = LoadGraph("video/flipleft1long.mp3");
    rightLongFlipHandle_ = LoadGraph("video/flipleft1.mp3");*/
}

//�X�V
void Transition::Update()
{
    if (canPlayTransition_)
    {
        PlayMovieToGraph(handle_);
        DrawGraph(transitionPositionX, transitionPositionY, handle_, true);

        ++transitionCount_;

        if (transitionCount_ > maxTransitionCount)
        {
            canPlayTransition_ = false;
            //DeleteGraph(handle_);
        }
    }
}

void Transition::Reset()
{
    PlayMovieToGraph(handle_);
    this->Init();
}
