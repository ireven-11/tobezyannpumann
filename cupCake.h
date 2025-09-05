#pragma once
#include"item.h"

//カップケーキ
class CupCake:public Item
{
public:
	CupCake();
	~CupCake();

	void cannotHealAllStamina_();	

	bool	GetisHealingStamina_()const { return isHealingAllStamin_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;				//アイテム効果（オーバーライド)

	bool isHealingAllStamin_;				//スタミナを回復するか
	const int   cupCakeSpawn_	= 60;		//出現確率
	const float speed_			= -1.0f;	//スピード
	const float spawnPositionY_ = 60.0f;	//スポーンポジション
	const float cupCakeHitboxX_	= 10.0f;	//ヒットボックスｘ
	const float cupCakeHitboxY_	= 10.0f;	//ヒットボックスy
};