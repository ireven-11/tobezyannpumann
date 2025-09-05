#pragma once

const int   minimumIconPositionX_	= 250;		//アイコン最小座標ｘ
const int   maxIconPositionX_		= 350;		//アイコン最大座標X
const int   minimumIconPositionY_	= 225;		//アイコン最小座標ｙ
const int   maxIconPositionY_		= 325;		//アイコン最大座標y
const VECTOR chanceGraphPosition	= VGet(800, 50, 0);	//チャンス画像座標

class Player;
class Effect;
class Timer;

//メモ
//アイテム出現確率有名なやつを調べて参考にする

//親クラス
class Item
{
public:
	Item();
	~Item();

	void Update_(Timer* timer, bool& cannotSpawnTwoItems, Player* player, Effect* effect);	//更新
	void Draw_(Player* player);																//描画
	void spawn_(Timer* timer, bool& cannotSpawnTwoItems);									//スポーン
	virtual void DrawEffectIcon_();															//効果アイコン描画
	virtual void decreseEffectCount_();														//アイテムカウント減少

	VECTOR Getposition_()const { return position_; }

protected:
	int    modelHandle_{};		//モデルハンドル
	VECTOR position_;			//座標
	int    randomSpawn_;		//出現確率
	bool   canExsist_;			//存在できるかフラグ
	int    spawnpercentage_;	//スポーン確立
	bool   canRollRandom_;		//確率を回せるかフラグ
	float  speedX_;				//速度（ｘ）
	float  speedY_;				//速度（ｙ）
	float  hitBoxX_;			//当たり判定の大きさx
	float  hitBoxY_;			//当たり判定の大きさy
	int	   effectCount_;		//アイテム効果カウント
	int    maxEffectCount_;		//アイテム効果最大カウント
	VECTOR spawnPosition_;		//スポーン座標
	int	   icon_;				//アイコン
	bool   isMovingRight_;		//右動きフラグ
	bool   isMovingLeft_;		//左動きフラグ
	bool   onDictionary_;		//図鑑に載るか

	const float itemScale_  = 0.050f;	//アイテムの大きさ
	const int   percentage_ = 100;		//%
	const float spawnRange	= 15;		//スポーン間隔
	const int   deleteTime	= 10;		//消滅時間

	virtual void itemEffect_();	//アイテムの効果
private:
	void move_(Player* player);									//移動
	bool takeItemJudge_(Player* player, Effect* effect);		//アイテムゲット当たり判定
	void resetPosition_(Player* player);						//ポジションリセット
	void deathpawn_(Timer* timer, bool& cannotSpawnTwoItems);	//デスポーン

	int		getItemSound_;	//アイテム入手音
	int		chanceGraph_;	//チャンスグラフ
	int		blinkcount_;	//点滅カウント

	const float turnMovingPosition_ = 90.0f;	//動きを帰る座標
};