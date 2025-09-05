#include"DxLib.h"
#include"sandClock.h"
#include"common.h"

SandClock::SandClock()
{
    spawnpercentage_    = sandClockSpawn_;
    modelHandle_        = MV1LoadModel("3dmodel/item/sandTimer/Parachute+sandTimer.mv1");
    speedY_             = speed_;
    hitBoxX_            = sandClockHitboxX_;
    hitBoxY_            = sandClockHitboxY_;
    spawnPosition_      = VGet(floatStandardNumber, spawnPositionY_, floatStandardNumber);
    isAddTimer_         = false;
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
}

SandClock::~SandClock()
{
    MV1DeleteModel(modelHandle_);
}

//�^�C�}�[�񕜂ł���悤�ɂ���
void SandClock::itemEffect_()
{
    isAddTimer_ = true;
}

//�^�C�}�[�񕜂ł��Ȃ��悤�ɂ���
void SandClock::cannotAddTimer_()
{
    isAddTimer_ = false;
}