#pragma once

const float transitionPositionX = 0.0f;	//トランジションx座標
const float transitionPositionY = 0.0f;	//トランジションｙ座標
const int	maxTransitionCount	= 45;	//最大トランジションカウント

class Transition
{
public:
	Transition();
	~Transition();

	void Init();	//初期化
	void Update();	//更新
	void Reset();	//リセット

	int GettransitionCount_()const { return transitionCount_; }
	int GetleftFlipHandle_()const { return leftFlipHandle_; }
	int GetrightFlipHandle_()const { return rightFlipHandle_; }
	int GetleftLongFlipHandle_()const { return leftLongFlipHandle_; }
	int GetrightLongFlipHandle_()const { return rightLongFlipHandle_; }

private:
	int   handle_;				//トランジションハンドル
	int   transitionCount_;     //トランジションカウント
	bool  canPlayTransition_;   //トランジションをながせるかフラグ
	int	  leftFlipHandle_;		//めくるトランジション（左)
	int	  rightFlipHandle_;		//めくるトランジション（右)
	int	  leftLongFlipHandle_;	//長くめくるトランジション（左)
	int	  rightLongFlipHandle_;	//長くめくるトランジション（右)
};