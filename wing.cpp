#include"DxLib.h"
#include"wing.h"
#include"common.h"
#include"player.h"

//コンストラクタ
Wing::Wing()
{
    spawnpercentage_    = wingSpawn;
    modelHandle_        = MV1LoadModel("3dmodel/item/wing/wing.mv1");
    speedX_             = wingSpeedX_;
    speedY_             = wingSpeedY_;
    hitBoxX_            = wingHitboxX_;
    hitBoxY_            = wingHitboxY_;
    maxEffectCount_     = maxWingEffectCount_;
    icon_               = LoadGraph("img/wing.png");
    spawnPosition_      = VGet(spawnPositionX_, floatStandardNumber, floatStandardNumber);
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
}

//デストラクタ
Wing::~Wing()
{
    MV1DeleteModel(modelHandle_);
    DeleteGraph(icon_);
}