#pragma once

const int		maxAnimationNumber				= 2;	//アニメーション最大数
const int		jumpAnimationFirstHalf			= 50;	//ジャンプアニメーション前半
const double	jumpAnimationSpeedFirstHalf		= 5.0;	//ジャンプアニメーション速度前半
const double	jumpAnimationSpeedSecondHalf	= 1.0;	//ジャンプアニメーション速度後半
const double	fallAnimationSpeed				= 2.0;	//落下アニメーション速度
const int		flyingAnimationSpeed			= 1.0f;	//飛ぶアニメーションスピード

class Player;
class Bird;

class Animation
{
public:
	Animation(Player* player, Bird* bird[]);
	~Animation();

	void Update(Player* player);				//更新
	void jumpReset_();							//ジャンプリセット
	void Init_(Player* player);					//初期化
	void UpdateFlying_(Bird* bird[]);			//飛ぶ更新
	void Delete_(Player* player, Bird* bird[]);	//デストラクタの代わり（引数を渡せないから）

private:
	int   animationHandle_[3];		//アニメーションハンドル
	int   jumpAnimation_;			//ジャンプアニメーション
	int	  fallAnimation_;			//落下アニメーション
	float jumpTotalTime_;			//ジャンプアニメーション総時間
	float jumpNowTime_;				//ジャンプアニメーション再生時間
	float fallTotalTime_;			//落下アニメーション総時間
	float fallNowTime_;				//落下アニメーション再生時間
	bool  isPlayingJumpAnimation_;	//ジャンプアニメーションがながれているか
	bool  isPlayingFallAnimation_;	//落下アニメーションが流れているか
	int   flyingAnimation_;			//飛ぶアニメーション
	float flyingTotalTime_;			//飛ぶ総時間
	float flyingNowTime_;			//飛ぶ再生時間
	float saveAnimation_;			//アニメーション保存
	bool  canAddSaveAnimation_;		//保存アニメーション加算できるか
	bool  isInitOneTime_;			//一回だけ初期化フラグ
};

