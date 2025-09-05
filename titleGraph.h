#pragma once

const int jumpUp                = 3;    //ジャンプ上昇量
const int randomJump            = 250;  //ジャンプ量（ランダム）
const int jumpmanWIDTHHEIGHT    = 100;  //ジャンプマンの幅と高さ

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();
    
    void Update_();
    void Draw_();
    void InitFlag_();

private:
    int  titleGraph_;           //タイトル画像
    int  cloud_[3];             //曇
    int  random_     = 0;       //ランダム
    bool isRandom_   = false;   //乱数するかフラグ
    int  shift_      = 0;       //ずらし量
    int  graph1x1_, graph1x2_;  //画像１のｘ座標
    int  graph2x1_, graph2x2_;  //画像2のｘ座標
    int  jumpGraph_;            //ジャンプ画像
    int  jumpX_;                //ジャンプｘ
    int  jumpY_;                //ジャンプｙ
    int  jumpCount_;            //ジャンプカウント
    int  maxJumpCount_;         //最大値ジャンプカウント
};

