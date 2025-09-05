#pragma once
#include"item.h"

//子クラス(盾)
class Shield :public Item
{
public:
	Shield();
	~Shield();

	int		GeteffectCount_()const { return effectCount_; }
	bool	GetcanProtectDamage_()const { return canProtectDamage_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

	void decreseEffectCount_() override;//アイテムカウント減少
	void DrawEffectIcon_() override;	//効果アイコン描画

private:
	void itemEffect_() override;					//アイテムの効果(オーバーライド)

	const int    shieldSpawn = 100;		//シールド出現確率
	const float  shieldSpeed = -1.0f;	//シールドスピード
	const int	 spawnPositionY_ = 70.0f;	//スポーンポジションY
	const float  shieldHitboxX_ = 10.0f;	//シールドヒットボックスｘ
	const float  shieldHitboxY_ = 15.0f;	//シールドヒットボックスy
	const int    maxShieldEffectCount_ = 250;		//最大エフェクトカウント
	const int    maxProtectDamageCount_ = 10;		//ダメージ防ぎ最大カウント

	bool		canProtectDamage_;					//ダメージ防げるかフラグ
};