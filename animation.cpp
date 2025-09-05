#include"DxLib.h"
#include"animation.h"
#include"common.h"
#include"player.h"
#include"bird.h"

//コンストラクタ
Animation::Animation(Player* player,Bird* bird[])
{
    //アニメーションを読み込み
    animationHandle_[1] = MV1LoadModel("animation/Floating.mv1");
    animationHandle_[0] = MV1LoadModel("animation/jump.mv1");
    animationHandle_[2] = MV1LoadModel("animation/flying.mv1");

    //アニメーションをアタッチ
    jumpAnimation_      = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[0]);
    flyingAnimation_    = MV1AttachAnim(bird[0]->GetmodelHandle_(), 0/*, animationHandle_[2]*/);

    //アニメーション総時間を取得
    fallTotalTime_      = MV1GetAnimTotalTime(player->GetmodelHandle_(), fallAnimation_);
    jumpTotalTime_      = MV1GetAnimTotalTime(player->GetmodelHandle_(), jumpAnimation_);
    flyingTotalTime_    = MV1GetAnimTotalTime(bird[0]->GetmodelHandle_(), flyingAnimation_);

    //アニメーション再生時間を初期化
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

//デストラクタ
Animation::~Animation()
{
    
}

//更新
void Animation::Update(Player* player)
{
    //ジャンプアニメーション再生(ため)
    if (player->GetcanStartJump_())
    {
        //一回だけnowtimeを初期化
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
        //再生時間をセット
        MV1SetAttachAnimTime(player->GetmodelHandle_(), jumpAnimation_, jumpNowTime_);
    }
    //ため放出
    else if (isPlayingJumpAnimation_)
    {
        //保存した分を加算
        if (canAddSaveAnimation_)
        {
            jumpNowTime_            += saveAnimation_;
            canAddSaveAnimation_    = false;
            isInitOneTime_          = true;
        }

        if (jumpNowTime_ < jumpAnimationFirstHalf)
        {
            jumpNowTime_ += jumpAnimationSpeedFirstHalf;//アニメーションの出始めだけ速度を早くする
        }
        else
        {
            jumpNowTime_ += jumpAnimationSpeedSecondHalf;
        }
        
        //落下するまでじゃんぷアニメーションをループさせる
        if (jumpNowTime_ > jumpTotalTime_ * -70)
        {
            jumpNowTime_ = jumpTotalTime_ * -70;
            //落下し始めたら落下アニメーションに移行
            if (player->GetjumpUpSpeed_() < floatStandardNumber || player->GetisFall_())
            {
                MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
                isPlayingJumpAnimation_ = false;
                fallAnimation_ = MV1AttachAnim(player->GetmodelHandle_(), 1, animationHandle_[1]);
                isPlayingFallAnimation_ = true;
            }
        }

        //再生時間をセット
        MV1SetAttachAnimTime(player->GetmodelHandle_(), jumpAnimation_, jumpNowTime_);
    }
    //落下アニメーション再生
    if (isPlayingFallAnimation_)
    {
        fallNowTime_ += fallAnimationSpeed;

        MV1SetAttachAnimTime(player->GetmodelHandle_(), fallAnimation_, fallNowTime_);

        //アニメーションループ
        if (fallNowTime_ > fallTotalTime_ * -110)
        {
            fallNowTime_ = floatStandardNumber;
        }
    }

    //地面についたら落下アニメーションをやめる
    if (player->Getposition_().y == floatStandardNumber && !player->GetcanStartJump_())
    {
        Init_(player);
    }
}

//ジャンプリセット
void Animation::jumpReset_()
{
    isPlayingJumpAnimation_ = true;
}

//飛ぶ更新
void Animation::UpdateFlying_(Bird* bird[])
{
    flyingNowTime_ += flyingAnimationSpeed;

    //アニメーションをループ
    if (flyingNowTime_ > flyingTotalTime_)
    {
        flyingNowTime_ = floatStandardNumber;
    }

    MV1SetAttachAnimTime(bird[0]->GetmodelHandle_(), flyingAnimation_, flyingNowTime_);
}

//初期化
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

//デストラクタの代わり
void Animation::Delete_(Player* player,Bird* bird[])
{
    MV1DetachAnim(player->GetmodelHandle_(), jumpAnimation_);
    MV1DetachAnim(bird[0]->GetmodelHandle_(), flyingAnimation_);
    MV1DetachAnim(player->GetmodelHandle_(), fallAnimation_);
}