#pragma once
#include"item.h"

const int abducteingRange = 5000;	//誘拐範囲

class UFO:public Item
{
public:
	UFO();
	~UFO();

	void cannotAbduct_();	//誘拐できない

	bool	GetcanAbduct_()const { return canAbduct_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;				//アイテム効果（オーバーライド)

	bool canAbduct_;	//誘拐できるかフラグ

	const int   ufoSpawn_		= 25;		//出現確率
	const float ufoSpeedX_		= 2.0f;		//スピード
	const float ufoSpeedY_		= 3.0f;		//スピード
	const float spawnPositionX_ = -145.0f;	//スポーンポジション
	const float ufoHitboxX_		= 20.0f;	//ヒットボックスｘ
	const float ufoHitboxY_		= 10.0f;	//ヒットボックスy
};