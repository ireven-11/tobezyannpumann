#include"DxLib.h"
#include"common.h"
#include"cupCake.h"

//�R���X�g���N�^
CupCake::CupCake()
{
	isHealingAllStamin_ = false;
    spawnpercentage_    = cupCakeSpawn_;
    modelHandle_        = MV1LoadModel("3dmodel/item/cake/Parachute+cupcake.mv1");
    speedY_             = speed_;
    hitBoxX_            = cupCakeHitboxX_;
    hitBoxY_            = cupCakeHitboxY_;
    spawnPosition_      = VGet(floatStandardNumber, spawnPositionY_, floatStandardNumber);
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
}

//�f�X�g���N�^
CupCake::~CupCake()
{
    
}

//�A�C�e������
void CupCake::itemEffect_()
{
    //���ʂ̋N��������������Č��ʖ{�̂�player�ŏ�������
	isHealingAllStamin_ = true;
}

//�X�^�~�i�S�񕜂��Ȃ�
void CupCake::cannotHealAllStamina_()
{
    //���ʏI������
	isHealingAllStamin_ = false;
}