#pragma once

//メモ
//敵の見た目を見るからに悪そうな見た目にすることで敵だとわかりやすくする例：クリボー

const int	maxBirdNumber			= 100;		//鳥の最大数
const float	resetPosition			= 90.00f;	//リセットポジション
const float intervalY				= 130.00f;	//鳥と鳥の間隔
const float standardSpeed			= 0.15f;	//基準スピード
const int	tutorialLeftBirdNumber	= 4;		//最初の4体は左から出てくる
const int	tutorialRightBirdNumber = 8;		//次の4体は右から出てくる
const int	drawUpRange				= 50;		//鳥の描画範囲(プレイヤーが鳥より上にいるとき)
const int	drawDownRange			= 85;		//鳥の描画範囲(プレイヤーが鳥より下にいるとき)

class Player;

class Bird
{
public:
	Bird(int& i);		//コンストラクタ
	~Bird();			//デストラクタ

	void Update_(int& i);				//更新
	void Draw_(Player* player, int& i);	//描画
	void Init_(int& i);					//初期化

	VECTOR Getposition_()const { return position_; }
	int	   GetmodelHandle_()const { return modelHandle_; }

private:
	int	   modelHandle_;			//モデルハンドル
	VECTOR position_;				//ポジション
	bool   isFromRight_ = false;	//右からくるかフラグ
	float  speed_		= 0.30f;	//スピード
	
	void InitPosition_(int& i);		//座標初期化
	void InitMove_(int& i);			//動き初期化
	void rotation_(int& i);			//向き回転				
};