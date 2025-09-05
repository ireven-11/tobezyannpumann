#pragma once

const float superJumpEffectPlayingSpeed		= 6.0f;	//スーパージャンプエフェクトの再生速度
const float jumpEffectPlayingSpeed			= 3.0f;	//ジャンプエフェクトの再生速度
const float itemGetEffectPlayingSpeed		= 1.5f;	//アイテムゲットエフェクトの再生速度
const float trajectoryEffectPlayingSpeed	= 5.0f;	//軌跡スピード
const float chargeEffectPlayingSpeed		= 55.0f;//チャージエフェクトの再生速度
const float shineSpeed						= 395.0f;//キラキラスピード

class Bird;
class Player;
class Item;

class Effect
{
public:
	Effect();
	~Effect();

	void UpdateSuperJump_(Bird* bird[], int& i);//スーパージャンプ更新
	void Draw_();								//描画
	void UpdateItemGet_(Player* player);		//アイテムゲット更新
	void UpdateTrajectory_(Player* player);		//軌跡更新
	void UpdateCharge_(Player* player);			//チャージ更新
	void kirakira_(Item* item);					//キラキラ更新
	void kirakiraCounter_();					//キラキラカウンター

private:
	int    superJumpEffect_;			//スーパージャンプエフェクト
	VECTOR superJumpEffectPosition_;	//スーパージャンプエフェクトポジション
	int    playingSuperJumpEffect_;		//再生中ハンドル（スーパージャンプ）
	VECTOR itemGetEffectPosition_;		//アイテムゲット座標
	int    itemGetEffect_;				//アイテムゲットエフェクト
	int    playingItemGetEffect_;		//再生中ハンドル(アイテムゲット)
	int	   trajectoryEffect_;			//軌跡エフェクト
	VECTOR trajectoryEffectPosition_;	//軌跡エフェクト座標
	int	   playingTrajectoryEffect_;	//再生中ハンドル(軌跡)
	int    trajectoryCount_;			//軌跡カウント
	int	   chargeEffect_;				//チャージエフェクト
	VECTOR chargeEffectPosition_;		//座標
	int	   playingChargeEffect_;		//再生中ハンドル
	int	   shine_;						//キラキラ
	int    shineCount_;					//カウント
	int	   playingShine_;				//プレイハンドル
};
