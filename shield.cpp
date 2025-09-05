#include"DxLib.h"
#include"shield.h"
#include"common.h"
#include"player.h"

//�R���X�g���N�^
Shield::Shield()
{
    spawnpercentage_        = shieldSpawn;
    modelHandle_            = MV1LoadModel("3dmodel/item/shield/Parachute+shield.mv1");
    speedX_                 = floatStandardNumber;
    speedY_                 = shieldSpeed;
    hitBoxX_                = shieldHitboxX_;
    hitBoxY_                = shieldHitboxY_;
    maxEffectCount_         = maxShieldEffectCount_;
    canProtectDamage_       = false;
    icon_                   = LoadGraph("img/shield.png");
    spawnPosition_          = VGet(floatStandardNumber, spawnPositionY_, floatStandardNumber);;
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
}

//�f�X�g���N�^
Shield::~Shield()
{
    MV1DeleteModel(modelHandle_);
    DeleteGraph(icon_);
}

//�_���[�W�h���J�E���g����
void Shield::decreseEffectCount_()
{
    if (canProtectDamage_)
    {
        --effectCount_;

        if (effectCount_ == standardNumber)
        {
            canProtectDamage_ = false;
        }
    }
}

//�A�C�e������
void Shield::itemEffect_()
{
    effectCount_ = maxEffectCount_;

    canProtectDamage_ = true;
}

//���ʃA�C�R���`��
void Shield::DrawEffectIcon_()
{
    if (canProtectDamage_ && effectCount_ > standardNumber)
    {
        DrawExtendGraph(minimumIconPositionX_, minimumIconPositionY_, maxIconPositionX_, maxIconPositionY_, icon_, TRUE);
    }
}