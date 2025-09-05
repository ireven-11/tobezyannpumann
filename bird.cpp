#include"DxLib.h"
#include"bird.h"
#include"common.h"
#include"player.h"

int model = -1;
int marker = -1;

//�R���X�g���N�^
Bird::Bird(int& i)
{
    //1�񂾂��ǂݍ��݂��邼
    if (model == -1)
    {
        model = MV1LoadModel("3dmodel/bird/banebird.mv1");
    }
    if (marker == -1)
    {
        marker = LoadGraph("img/arrow.png");
    }

    modelHandle_ = model;
    //markerHandle_ = marker;

    //���f���̑傫���𒲐�
    MV1SetScale(modelHandle_,VGet(0.10f,0.10f,0.10f));

    Init_(i);
}

//�f�X�g���N�^
Bird::~Bird()
{
    MV1DeleteModel(modelHandle_);
    MV1DeleteModel(model);
}

//���W������
void Bird::InitPosition_(int& i)
{
    if (i < tutorialLeftBirdNumber)
    {
        position_ = VGet(-resetPosition, i * intervalY, floatStandardNumber);
    }
    else if (i >= tutorialLeftBirdNumber && i < tutorialRightBirdNumber)
    {
        position_ = VGet(resetPosition, i * intervalY, floatStandardNumber);
    }
    else
    {
        if (!isFromRight_)
        {
            position_ = VGet(-resetPosition, i * intervalY, floatStandardNumber);
        }
        else
        {
            position_ = VGet(resetPosition, i * intervalY, floatStandardNumber);
        }
    }
}

//����������
void Bird::InitMove_(int& i)
{
    if (GetRand(1) == 0)
    {
        isFromRight_ = false;
    }
    else
    {
        isFromRight_ = true;
    }

    //�ŏ��̓z�炾�����񓯂�����������
    if (i < tutorialLeftBirdNumber)
    {
        isFromRight_ = false;
    }
    if (i >= tutorialLeftBirdNumber && i < tutorialRightBirdNumber)
    {
        isFromRight_ = true;
    }

    if (i >= tutorialRightBirdNumber)
    {
        speed_ = GetRand(2);
        if (speed_ == standardNumber)
        {
            speed_ = standardSpeed;
        }
        else if (speed_ == 1)
        {
            speed_ = standardSpeed * 2;
        }
        else
        {
            speed_ = standardSpeed * 3;
        }
    }
    else
    {
        speed_ = standardSpeed;
    }
}

//������
void Bird::Init_(int& i)
{
    InitMove_(i);
    InitPosition_(i);
}

//�X�V
void Bird::Update_(int& i)
{
    //�ړ�
    if (!isFromRight_)
    {
        position_.x += speed_;
        if (position_.x > resetPosition)
        {
            position_.x = -resetPosition;//�����l�ɖ߂�
        }
    }
    else
    {
        position_.x -= speed_;
        if (position_.x < -resetPosition)
        {
            position_.x = +resetPosition;//�����l�ɖ߂�
        }
    }
}

//������]
void Bird::rotation_(int& i)
{
    //���f������]
    if (i < tutorialLeftBirdNumber)
    {
        MV1SetRotationXYZ(modelHandle_, VGet(0.00f * DX_PI_F / 180.00f, 270.00f * DX_PI_F / 180.00f, 0.00f));
    }
    else if (i >= tutorialLeftBirdNumber && i < tutorialRightBirdNumber)
    {
        MV1SetRotationXYZ(modelHandle_, VGet(0.00f * DX_PI_F / 180.00f, 90.00f * DX_PI_F / 180.00f, 0.00f));
    }
    else
    {
        if (!isFromRight_)
        {
            MV1SetRotationXYZ(modelHandle_, VGet(0.00f * DX_PI_F / 180.00f, 270.00f * DX_PI_F / 180.00f, 0.00f));
        }
        else
        {
            MV1SetRotationXYZ(modelHandle_, VGet(0.00f * DX_PI_F / 180.00f, 90.00f * DX_PI_F / 180.00f, 0.00f));
        }
    }
}

//�`��
void Bird::Draw_(Player* player,int& i)
{
    rotation_(i);

    //�v���C���[�ƒ�������Ă���Ƃ��͕`�悵�Ȃ�
    if (player->Getposition_().y - Getposition_().y < drawUpRange &&  player->Getposition_().y - Getposition_().y > -drawDownRange)
    {
        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle_, position_);

        MV1DrawModel(modelHandle_);
    }
    
}