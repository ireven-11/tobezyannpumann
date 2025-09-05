#include"DxLib.h"
#include"camera.h"
#include"player.h"
#include"common.h"
#include"EffekseerForDXLib.h"

//�R���X�g���N�^
Camera::Camera()
{
    position_.x         = floatStandardNumber;
    position_.y         = initY;
    position_.z         = initZ;
    targetPosition_.x   = floatStandardNumber;
    targetPosition_.y   = initTargetY;
    targetPosition_.z   = floatStandardNumber;
}

//�f�X�g���N�^
Camera::~Camera()
{
}

//�X�V
void Camera::Update_(Player* player)
{
    //���s1�`100�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(1.00f, 100.00f);

    // DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
    Effekseer_Sync3DSetting();

    //�d�͂�W�����v�ɍ��킹�ăJ�����̈ʒu��ς���
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

    //�^�[�Q�b�g������p�x�ɃJ������ݒu
    SetCameraPositionAndTarget_UpVecY(VGet(position_.x, position_.y, position_.z), VGet(targetPosition_.x, targetPosition_.y, targetPosition_.z));
    //SetCameraPositionAndAngle(position_, rote, floatStandardNumber, floatStandardNumber);
}