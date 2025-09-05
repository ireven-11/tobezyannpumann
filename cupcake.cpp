#include"DxLib.h"
#include"common.h"
#include"cupCake.h"

//コンストラクタ
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

//デストラクタ
CupCake::~CupCake()
{
    
}

//アイテム効果
void CupCake::itemEffect_()
{
    //効果の起動処理だけやって効果本体はplayerで処理する
	isHealingAllStamin_ = true;
}

//スタミナ全回復しない
void CupCake::cannotHealAllStamina_()
{
    //効果終了処理
	isHealingAllStamin_ = false;
}