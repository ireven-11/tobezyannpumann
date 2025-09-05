#include"DxLib.h"
#include"bird.h"
#include"common.h"
#include"player.h"

int model = -1;
int marker = -1;

//コンストラクタ
Bird::Bird(int& i)
{
    //1回だけ読み込みするぞ
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

    //モデルの大きさを調整
    MV1SetScale(modelHandle_,VGet(0.10f,0.10f,0.10f));

    Init_(i);
}

//デストラクタ
Bird::~Bird()
{
    MV1DeleteModel(modelHandle_);
    MV1DeleteModel(model);
}

//座標初期化
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

//動き初期化
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

    //最初の奴らだけ毎回同じ動きをする
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

//初期化
void Bird::Init_(int& i)
{
    InitMove_(i);
    InitPosition_(i);
}

//更新
void Bird::Update_(int& i)
{
    //移動
    if (!isFromRight_)
    {
        position_.x += speed_;
        if (position_.x > resetPosition)
        {
            position_.x = -resetPosition;//初期値に戻す
        }
    }
    else
    {
        position_.x -= speed_;
        if (position_.x < -resetPosition)
        {
            position_.x = +resetPosition;//初期値に戻す
        }
    }
}

//向き回転
void Bird::rotation_(int& i)
{
    //モデルを回転
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

//描画
void Bird::Draw_(Player* player,int& i)
{
    rotation_(i);

    //プレイヤーと鳥が離れているときは描画しない
    if (player->Getposition_().y - Getposition_().y < drawUpRange &&  player->Getposition_().y - Getposition_().y > -drawDownRange)
    {
        // ３Dモデルのポジション設定
        MV1SetPosition(modelHandle_, position_);

        MV1DrawModel(modelHandle_);
    }
    
}