#include"DxLib.h"
#include"rocket.h"
#include"common.h"
#include"player.h"

//コンストラクタ
Rocket::Rocket()
{
    spawnpercentage_    = rocketSpawn;
    modelHandle_        = MV1LoadModel("3dmodel/item/rocket/rocket.mv1");
    speedX_             = floatStandardNumber;
    speedY_             = rocketSpeed;
    hitBoxX_            = rocketHitboxX_;
    hitBoxY_            = rocketHitboxY_;
    spawnPosition_      = VGet(floatStandardNumber, spawnPositionY_, floatStandardNumber);
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
    maxEffectCount_     = maxRocketEffectCount_;
}

//デストラクタ
Rocket::~Rocket()
{
    MV1DeleteModel(modelHandle_);
}

//ロケットに乗る
void Rocket::ride_(Player* player)
{
    if (effectCount_ > standardNumber)
    {
        position_ = player->Getposition_();
        player->ridingRocket_();
        MV1DrawModel(modelHandle_);
        MV1SetPosition(modelHandle_, position_);
    }
}