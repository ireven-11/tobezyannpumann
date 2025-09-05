#include"DxLib.h"
#include"titleGraph.h"
#include"common.h"

//コンストラクタ
TitleGraph::TitleGraph()
{
    titleGraph_ = LoadGraph("img/Clouds//Clouds 5/1.png");
    cloud_[0]   = LoadGraph("img/Clouds//Clouds 1/4.png");
    cloud_[1]   = LoadGraph("img/Clouds//Clouds 5/5.png");
    cloud_[2]   = LoadGraph("img/Clouds//Clouds 5/3.png");
    jumpGraph_  = LoadGraph("img/jump.png");
    jumpX_      = screenWIDTH;
    jumpY_      = screenHEIGHT;
}

//デストラクタ
TitleGraph::~TitleGraph()
{
    DeleteGraph(titleGraph_);
    DeleteGraph(cloud_[0]);
    DeleteGraph(cloud_[1]);
    DeleteGraph(cloud_[2]);
    DeleteGraph(jumpGraph_);
}

//更新
void TitleGraph::Update_()
{
    //1回だけランダムにする
    if (!isRandom_)
    {
        random_     = GetRand(2);
        isRandom_   = true;
    }

    //ずらし量を増やす
    ++shift_;

    graph1x1_ = standardNumber + shift_;
    graph1x2_ = screenWIDTH + shift_;
    graph2x1_ = standardNumber + shift_ - screenWIDTH;
    graph2x2_ = standardNumber + shift_;

    //2枚の画像をループさせる
    if (graph1x1_ > screenWIDTH)
    {
        graph1x1_   = -screenWIDTH;
        graph1x2_   = standardNumber;
        shift_      = standardNumber;
    }
    if (graph2x1_ > screenWIDTH)
    {
        graph2x1_   = -screenWIDTH;
        graph2x2_   = standardNumber;
        shift_      = standardNumber;
    }

    //乱数でジャンプの位置を変更
    if (jumpY_ > screenHEIGHT)
    {
        jumpCount_      = standardNumber;
        jumpX_          = GetRand(screenHEIGHT);
        maxJumpCount_   = GetRand(randomJump);
    }

    //ジャンプ
    ++jumpCount_;
    if (jumpCount_ < maxJumpCount_)
    {
        jumpY_ -= jumpUp;
    }
    else
    {
        jumpY_ += jumpUp;
    }
}

//描画
void TitleGraph::Draw_()
{
    DrawExtendGraph(standardNumber, standardNumber, screenWIDTH, screenHEIGHT, titleGraph_, TRUE);
    DrawExtendGraph(graph1x1_, standardNumber, graph1x2_, screenHEIGHT, cloud_[random_], TRUE);
    DrawExtendGraph(graph2x1_, standardNumber, graph2x2_, screenHEIGHT, cloud_[random_], TRUE);
    DrawExtendGraph(jumpX_, jumpY_, jumpX_ + jumpmanWIDTHHEIGHT, jumpY_ + jumpmanWIDTHHEIGHT, jumpGraph_,TRUE);
}

//フラグを初期化
void TitleGraph::InitFlag_()
{
    isRandom_ = false;
}