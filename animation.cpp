#include"DxLib.h"
#include"animation.h"
#include"common.h"
#include"player.h"
#include"bird.h"

//�R���X�g���N�^
Animation::Animation(Player* player,Bird* bird[])
{
    //�A�j���[�V������ǂݍ���
    animationHandle_[1] = MV1LoadModel("animation/Floating.mv1");
    animationHandle_[0] = MV1LoadModel("animation/jump.mv1");
    animationHandle_[2] = MV1LoadModel("animation/flying.mv1");

    //�A�j���[�V�������A�^�b�`
    jumpAnimation_      = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[0]);
    flyingAnimation_    = MV1AttachAnim(bird[0]->GetmodelHandle_(), 0/*, animationHandle_[2]*/);

    //�A�j���[�V���������Ԃ��擾
    fallTotalTime_      = MV1GetAnimTotalTime(player->GetmodelHandle_(), fallAnimation_);
    jumpTotalTime_      = MV1GetAnimTotalTime(player->GetmodelHandle_(), jumpAnimation_);
    flyingTotalTime_    = MV1GetAnimTotalTime(bird[0]->GetmodelHandle_(), flyingAnimation_);

    //�A�j���[�V�����Đ����Ԃ�������
    fallNowTime_        = floatStandardNumber;
    MV1SetAttachAnimTime(player->GetmodelHandle_(), fallAnimation_, fallNowTime_);
    jumpNowTime_        = floatStandardNumber;
    MV1SetAttachAnimTime(player->GetmodelHandle_(), jumpAnimation_, jumpNowTime_);
    flyingNowTime_      = floatStandardNumber;
    MV1SetAttachAnimTime(bird[0]->GetmodelHandle_(), flyingAnimation_, flyingNowTime_);

    isPlayingJumpAnimation_ = false;
    isPlayingFallAnimation_ = false;
    canAddSaveAnimation_    = false;
    isInitOneTime_          = true;
    saveAnimation_          = floatStandardNumber;
}

//�f�X�g���N�^
Animation::~Animation()
{
    
}

//�X�V
void Animation::Update(Player* player)
{
    //�W�����v�A�j���[�V�����Đ�(����)
    if (player->GetcanStartJump_())
    {
        //��񂾂�nowtime��������
        if (isInitOneTime_)
        {
            jumpNowTime_            = floatStandardNumber;
            isInitOneTime_          = false;
            isPlayingFallAnimation_ = false;
            MV1DetachAnim(player->GetmodelHandle_(), fallAnimation_);
            MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
            jumpAnimation_ = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[0]);
        }

        jumpNowTime_ += jumpAnimationSpeedFirstHalf;

        if (jumpNowTime_ > jumpTotalTime_ * -25)
        {
            jumpNowTime_ = jumpTotalTime_ * -25;
        }
        saveAnimation_          = jumpNowTime_;
        canAddSaveAnimation_    = true;
        //�Đ����Ԃ��Z�b�g
        MV1SetAttachAnimTime(player->GetmodelHandle_(), jumpAnimation_, jumpNowTime_);
    }
    //���ߕ��o
    else if (isPlayingJumpAnimation_)
    {
        //�ۑ������������Z
        if (canAddSaveAnimation_)
        {
            jumpNowTime_            += saveAnimation_;
            canAddSaveAnimation_    = false;
            isInitOneTime_          = true;
        }

        if (jumpNowTime_ < jumpAnimationFirstHalf)
        {
            jumpNowTime_ += jumpAnimationSpeedFirstHalf;//�A�j���[�V�����̏o�n�߂������x�𑁂�����
        }
        else
        {
            jumpNowTime_ += jumpAnimationSpeedSecondHalf;
        }
        
        //��������܂ł����ՃA�j���[�V���������[�v������
        if (jumpNowTime_ > jumpTotalTime_ * -70)
        {
            jumpNowTime_ = jumpTotalTime_ * -70;
            //�������n�߂��痎���A�j���[�V�����Ɉڍs
            if (player->GetjumpUpSpeed_() < floatStandardNumber || player->GetisFall_())
            {
                MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
                isPlayingJumpAnimation_ = false;
                fallAnimation_ = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[1]);
                isPlayingFallAnimation_ = true;
            }
        }

        //�Đ����Ԃ��Z�b�g
        MV1SetAttachAnimTime(player->GetmodelHandle_(), jumpAnimation_, jumpNowTime_);
    }
    //�����A�j���[�V�����Đ�
    if (isPlayingFallAnimation_)
    {
        fallNowTime_ += fallAnimationSpeed;

        MV1SetAttachAnimTime(player->GetmodelHandle_(), fallAnimation_, fallNowTime_);

        //�A�j���[�V�������[�v
        if (fallNowTime_ > fallTotalTime_ * -110)
        {
            fallNowTime_ = floatStandardNumber;
        }
    }

    //�n�ʂɂ����痎���A�j���[�V��������߂�
    if (player->Getposition_().y == floatStandardNumber && !player->GetcanStartJump_())
    {
        Init_(player);
    }
}

//�W�����v���Z�b�g
void Animation::jumpReset_()
{
    isPlayingJumpAnimation_ = true;
}

//��ԍX�V
void Animation::UpdateFlying_(Bird* bird[])
{
    flyingNowTime_ += flyingAnimationSpeed;

    //�A�j���[�V���������[�v
    if (flyingNowTime_ > flyingTotalTime_)
    {
        flyingNowTime_ = floatStandardNumber;
    }

    MV1SetAttachAnimTime(bird[0]->GetmodelHandle_(), flyingAnimation_, flyingNowTime_);
}

//������
void Animation::Init_(Player* player)
{
    jumpNowTime_            = floatStandardNumber;
    fallNowTime_            = floatStandardNumber;
    isPlayingJumpAnimation_ = false;
    isPlayingFallAnimation_ = false;
    MV1DetachAnim(player->GetmodelHandle_(), fallAnimation_);
    MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
    jumpAnimation_ = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[0]);
}

//�f�X�g���N�^�̑���
void Animation::Delete_(Player* player,Bird* bird[])
{
    MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
    MV1DetachAnim(bird[0]->GetmodelHandle_(), flyingAnimation_);
    MV1DetachAnim(player->GetmodelHandle_(), fallAnimation_);
}