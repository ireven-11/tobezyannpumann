#include"DxLib.h"
#include"camera.h"
#include"player.h"
#include"common.h"
#include"EffekseerForDXLib.h"

//コンストラクタ
Camera::Camera()
{
    position_.x         = floatStandardNumber;
    position_.y         = initY;
    position_.z         = initZ;
    targetPosition_.x   = floatStandardNumber;
    targetPosition_.y   = initTargetY;
    targetPosition_.z   = floatStandardNumber;
}

//デストラクタ
Camera::~Camera()
{
}

//更新
void Camera::Update_(Player* player)
{
    //奥行1～100までをカメラの描画範囲とする
    SetCameraNearFar(1.00f, 100.00f);

    // DXライブラリのカメラとEffekseerのカメラを同期する。
    Effekseer_Sync3DSetting();

    //重力やジャンプに合わせてカメラの位置を変える
    if (player->GetisFall_())
    {
        ++fallCount_;

        if (fallCount_ > maxFallCount)
        {
            fallCount_ = maxFallCount;
        }
    }
    else if(!player->GetisFall_())
    {
        fallCount_ -= subFallCount;
        if (fallCount_ < minimumFallCount)
        {
            fallCount_ = minimumFallCount;
        }
    }
    if (player->Getposition_().y == floatStandardNumber)
    {
        fallCount_ = standardNumber;
    }
    position_.y         = initY + player->Getposition_().y + fallCount_;
    targetPosition_.y   = initTargetY + player->Getposition_().y + fallCount_;

    //float rote= DX_PI_F / fallCount_;

    //ターゲットを見る角度にカメラを設置
    SetCameraPositionAndTarget_UpVecY(VGet(position_.x, position_.y, position_.z), VGet(targetPosition_.x, targetPosition_.y, targetPosition_.z));
    //SetCameraPositionAndAngle(position_, rote, floatStandardNumber, floatStandardNumber);
}