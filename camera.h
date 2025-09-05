#pragma once

const int	maxFallCount		= 10;		//最大落下カウント
const int	minimumFallCount	= -10;		//最小落下カウント
const float	initZ				= -75.00f;	//カメラ初期Z
const float initY				= 15.00f;	//カメラ初期Y
const float initTargetY			= 10.00f;	//ターゲット初期Y
const int	subFallCount		= 3;		//カメラ落下減少速度		

class Player;

class Camera
{
public:
	Camera();						//コンストラクタ
	~Camera();						//デストラクタ

	void Update_(Player* player);	//更新

private:
	VECTOR position_;		//カメラポジション
	VECTOR targetPosition_;	//カメラのターゲットポジション
	int	   fallCount_ = 0;	//落下カウント
};