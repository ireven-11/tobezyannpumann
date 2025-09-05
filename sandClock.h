#pragma once
#include"item.h"

class SandClock:public Item
{
public:
	SandClock();
	~SandClock();

	void cannotAddTimer_();	//タイマーを増やせなくする

	bool	GetisAddTimer_()const { return isAddTimer_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;					//アイテム効果（オーバーライド)

	bool isAddTimer_;

	const int   sandClockSpawn_		= 70;		//出現確率
	const float speed_				= -1.0f;	//スピード
	const float spawnPositionY_		= 120.0f;	//スポーンポジション
	const float sandClockHitboxX_	= 10.0f;	//ヒットボックスｘ
	const float sandClockHitboxY_	= 10.0f;	//ヒットボックスy
};