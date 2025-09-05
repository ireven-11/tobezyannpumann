#pragma once

const float  maxJumpSpeed			= 2.5f;		//ジャンプ最大速度
const float  velocity				= 0.30f;	//加速度
const float  maxXSpeed				= 2.50f;	//最大値移動量
const float  gravityVelocity		= 0.10f;	//重力加速度
const float  maxGravityVelocity		= 3.00f;	//最大重力加速度
const int	 maxInvincibleCount		= 120;		//最大無敵カウント
const double consumingStamina		= 1.0;		//消費スタミナ
const float  maxSuperJumpCount		= 250.00f;	//スーパージャンプ最大カウント
const float  playerXMIN				= -65.00f;	//プレイヤーのｘ座標最小値
const float  playerXMAX				= 65.00f;	//プレイヤーのｘ座標最大値
const int	 maxStamina				= 100;		//スタミナ最大値
const double damageStamina			= 20.00;	//ダメージを受けたときの消費スタミナ
const int	 addMaxNormalJumpCount	= 5;		//最大ノーマルジャンプカウント加算量
const float  ridingRocketSpeed		= 10.0f;	//乗車中のロケットスピード
const int    maxStaminaCount_		= 1000;		//最大スタミナカウント
const float  minimumJumpUPSpeed		= -2.00f;	//最小ジャンプ速度

class Bird;
class Animation;
class Effect;
class Shield;
class Wing;
class Rocket;
class CupCake;
class UFO;
class ChargeEffect;

class Player
{
public:
	Player();																													//コンストラクタ
	~Player();																													//デストラクタ

	void Init_();																												//初期化
	void Update_(Animation* animation, Player* player, Effect* effect, Wing* wing, Rocket* rocket, CupCake* cupCake, UFO* ufo,
		ChargeEffect* chargeEffect);	//更新
	void Draw_(Rocket* rocket);																									//描画
	void invincibleTime_(Player* player, Bird* bird[], Effect* effect,Shield* shield);											//無敵時間関数
	void changeJumpType(Player* player, Bird* bird[], Effect* effect);															//ジャンプ切り替え
	void ridingRocket_();																										//ロケット乗車中

	//ゲッター
	VECTOR Getposition_()const { return position_; }
	float  Getgravity_()const { return gravity_; }
	bool   GetisFall_()const { return isFall_; }
	double Getstamina_()const { return stamina_; }
	int	   GetmodelHandle_()const { return modelHandle_; }
	bool   GetisSuperJump_()const { return isSuperJump_; }
	float  GetjumpUpSpeed_()const { return jumpUpSpeed_; }
	bool   GetcanStartJump_()const { return canStartJump_; }
	int	   GetconsumingStaminaCount_()const { return consumingStaminaCount_; }
	float  GetmaxNormalJumpCount_()const { return maxNormalJumpCount_; }

private:
	int	   modelHandle_;						//モデルハンドル
	VECTOR position_;							//ポジション
	bool   isPrevSpace_				= false;	//スペース長押し検知フラグ
	int	   jumpCount_				= 0;		//ジャンプカウント
	bool   isJumpCount_				= false;	//ジャンプカウントフラグ
	float  jumpUpSpeed_				= 0.00f;	//ジャンプ上昇量
	float  gravity_					= 0.00f;	//重力
	bool   isFall_					= false;	//落ちているかフラグ
	float  xAddSpeed_				= 0.00f;	//x座標の+移動量
	float  xSubtractSpeed_			= 0.00f;	//x座標の-移動量
	bool   isInvincible_			= false;	//無敵フラグ
	int    invincibleCount_			= 0;		//無敵カウント
	double stamina_					= 0.00;		//スタミナ
	int    staminaCount_			= 0;		//スタミナカウント
	float  maxJumpCount_			= 70.00f;	//最大ジャンプカウント
	bool   isSuperJump_				= false;	//スーパージャンプするかフラグ
	int	   superJumpSound_;						//スーパージャンプサウンド
	int    jumpSound_;							//ジャンプサウンド
	int	   damageSound_;						//ダメージサウンド
	bool   isFacingRight			= true;		//右向きフラグ
	bool   canStartJump_			= false;	//ジャンプ開始できるかフラグ
	float  maxNormalJumpCount_		= 0.00f;	//通常ジャンプ最大カウント
	int	   consumingStaminaCount_	= 0;		//消費スタミナカウント
	int	   chargingSound_;						//チャージ音
	bool   canStartChargingSound_	= true;		//チャージ音開始できるか

	void   jump_(Animation* animation, Player* player, Effect* effect, Wing* wing);	//ジャンプ関数
	void   nowJump_();																//ジャンプ中関数
	void   chargeJump_(Effect* effect, ChargeEffect* chargeEffect);					//ジャンプ貯める関数
	void   moveX_();																//横移動
	void   facing_();																//どっち向き
	void   pushBack_();																//押し戻し
	void   healStamina_();															//スタミナ回復
	void   allHealStamina_(CupCake* cupCake);										//スタミナ全回復
	void   abducted_(UFO* ufo);														//誘拐される				
};