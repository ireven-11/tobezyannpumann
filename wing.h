#pragma once
#include"item.h"

//子クラス(羽)
class Wing :public Item
{
public:
	Wing();
	~Wing();

	int		GeteffectCount_()const { return effectCount_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	const int   wingSpawn			= 45;		//羽出現確率
	const float wingSpeedX_			= 2.0f;		//羽スピード
	const float wingSpeedY_			= 3.0f;		//羽スピード
	const float spawnPositionX_		= -150.0f;	//スポーンポジション
	const float wingHitboxX_		= 15.0f;	//羽ヒットボックスｘ
	const float wingHitboxY_		= 10.0f;	//羽ヒットボックスy
	const int   maxWingEffectCount_ = 2;		//最大エフェクトカウント
};