#include"DxLib.h"
#include"ufo.h"
#include"common.h"

UFO::UFO()
{
    spawnpercentage_    = ufoSpawn_;
    modelHandle_        = MV1LoadModel("3dmodel/item/ufo/UFO.mv1");
    speedX_             = ufoSpeedX_;
    speedY_             = ufoSpeedY_;
    hitBoxX_            = ufoHitboxX_;
    hitBoxY_            = ufoHitboxY_;
    spawnPosition_      = VGet(spawnPositionX_, floatStandardNumber, floatStandardNumber);
    canAbduct_          = false;
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
}

UFO::~UFO()
{
    MV1DeleteModel(modelHandle_);
}

void UFO::itemEffect_()
{
    //Œø‰Ê‹N“®ˆ—‚¾‚¯‚â‚Á‚ÄŒø‰Ê–{‘Ì‚Íplayer‚Åˆ—‚·‚é
    canAbduct_ = true;
}

void UFO::cannotAbduct_()
{
    //Œø‰ÊI—¹ˆ—
    canAbduct_ = false;
}