#pragma once
#include"item.h"

class Player;

//子クラス(ロケット)
class Rocket :public Item
{
public:
	Rocket();
	~Rocket();

	void ride_(Player* player);

	int		GeteffectCount_()const { return effectCount_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	const int   rocketSpawn = 10;		//ロケット出現確率
	const float rocketSpeed = 5.0f;		//ロケットスピード
	const float spawnPositionY_ = -100.0f;	//スポーンポジション
	const float rocketHitboxX_ = 5.0f;		//ロケットヒットボックスｘ
	const float rocketHitboxY_ = 5.0f;		//ロケットヒットボックスy
	const int	maxRocketEffectCount_ = 100;		//最大値エフェクトカウント
};