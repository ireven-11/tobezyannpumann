#include"DxLib.h"
#include"player.h"
#include"common.h"
#include"bird.h"
#include"collision.h"
#include"animation.h"
#include"effect.h"
#include"rocket.h"
#include"shield.h"
#include"wing.h"
#include"cupCake.h"
#include"ufo.h"
#include"chargeEffect.h"

//コンストラクタ
Player::Player()
{
	// ３Ｄモデルの読み込み
	modelHandle_	= MV1LoadModel("3dmodel/human/redMan.mv1");

	superJumpSound_	= LoadSoundMem("sound/superjump.mp3");
	jumpSound_		= LoadSoundMem("sound/jump.mp3");
	chargingSound_	= LoadSoundMem("sound/charge.mp3");
	ChangeVolumeSoundMem(150, superJumpSound_);
	ChangeVolumeSoundMem(125, jumpSound_);
	ChangeVolumeSoundMem(200, chargingSound_);

	MV1SetScale(modelHandle_,VGet(0.10f,0.10f,0.10f));

	position_ = VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);

	damageSound_ = LoadSoundMem("sound/damage.mp3");
	ChangeVolumeSoundMem(250, damageSound_);
}

//デストラクタ
Player::~Player()
{
	MV1DeleteModel(modelHandle_);
	DeleteSoundMem(superJumpSound_);
	DeleteSoundMem(jumpSound_);
	DeleteSoundMem(damageSound_);
}

//初期化
void Player::Init_()
{
	position_			= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	MV1SetPosition(modelHandle_, position_);
	MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber));
	isPrevSpace_		= false;
	jumpCount_			= standardNumber;
	isJumpCount_		= false;
	jumpUpSpeed_		= floatStandardNumber;
	gravity_			= floatStandardNumber;
	isFall_				= false;
	xAddSpeed_			= floatStandardNumber;
	xSubtractSpeed_		= floatStandardNumber;
	isInvincible_		= false;
	invincibleCount_	= standardNumber;
	stamina_			= floatStandardNumber;
	staminaCount_		= standardNumber;
	isFacingRight		= true;
	maxNormalJumpCount_ = floatStandardNumber;
	canStartJump_		= false;
	canStartChargingSound_ = false;
}

//更新
void Player::Update_(Animation* animation, Player* player, Effect* effect,Wing* wing,Rocket* rocket,CupCake* cupCake,UFO* ufo,ChargeEffect* chargeEffect)
{
	//横移動
	moveX_();

	//どっち向き
	facing_();

	//ジャンプ関数を呼び出し
	jump_(animation,this,effect,wing);

	//ジャンプ貯める関数を呼び出し
	chargeJump_(effect,chargeEffect);

	//スタミナ回復
	healStamina_();

	//スタミナ全回復
	allHealStamina_(cupCake);
	
	//押し戻し
	pushBack_();

	//軌跡エフェクト
	effect->UpdateTrajectory_(this);

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle_, position_);

	//ロケット
	rocket->decreseEffectCount_();
	rocket->ride_(this);

	//ufoに誘拐される
	abducted_(ufo);
}

//ジャンプ
void Player::jump_(Animation* animation, Player* player, Effect* effect, Wing* wing)
{
	//スペースをはなしてジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) == false && canStartJump_|| isSuperJump_)
	{
		if (!isPrevSpace_)
		{
			//事前準備
			consumingStaminaCount_ = standardNumber;
			canStartJump_	= false;
			isJumpCount_	= true;
			jumpUpSpeed_	= maxJumpSpeed;
			jumpCount_		= standardNumber;
			gravity_		= floatStandardNumber;
			isFall_			= false;
			StopSoundMem(chargingSound_, standardNumber);
			canStartChargingSound_ = true;
			animation->Init_(player);
			animation->jumpReset_();
			wing->decreseEffectCount_();
			if (isSuperJump_)
			{
				maxJumpCount_ = maxSuperJumpCount;
				if (wing->GeteffectCount_() > standardNumber)
				{
					maxJumpCount_ *= 2;
				}
				PlaySoundMem(superJumpSound_, DX_PLAYTYPE_BACK, TRUE);
			}
			else
			{
				maxJumpCount_ = maxNormalJumpCount_ * 2;
				if (wing->GeteffectCount_() > standardNumber)
				{
					maxJumpCount_ *= 2;
				}
				maxNormalJumpCount_ = floatStandardNumber;
				PlaySoundMem(jumpSound_, DX_PLAYTYPE_BACK, TRUE);
			}

			isPrevSpace_ = true;
			isSuperJump_ = false;
		}
		else
		{
			isPrevSpace_ = false;
			isSuperJump_ = false;
		}
	}

	//ジャンプ中関数を呼び出し
	nowJump_();

	//ジャンプしていない時は重力が発生
	if (!isJumpCount_ && position_.y != floatStandardNumber)
	{
		if (maxGravityVelocity > gravity_)
		{
			gravity_ += gravityVelocity;
		}
		position_.y -= gravity_;
	}
}

//ジャンプ切り替え
void Player::changeJumpType(Player* player, Bird* bird[], Effect* effect)
{
	//通常ジャンプとスーパージャンプの切り替え
	if (!isSuperJump_)
	{
		isSuperJump_ = superJump(this, bird,effect);
	}
}

//ジャンプ中関数
void Player::nowJump_()
{
	//カウントが一定になるまではジャンプを続ける
	if (jumpCount_ < maxJumpCount_ && isJumpCount_)
	{
		position_.y += jumpUpSpeed_;
		++jumpCount_;
		
		if (jumpCount_ > maxJumpCount_ / 5)
		{
			//最大落下速度を重力が超えてなかったら重力加速度を足す
			if (maxGravityVelocity > gravity_)
			{
				gravity_ += gravityVelocity;
			}
			jumpUpSpeed_ -= gravity_;

			//最小ジャンプスピードより小さくなったら元に戻す
			if (minimumJumpUPSpeed > jumpUpSpeed_)
			{
				jumpUpSpeed_ = minimumJumpUPSpeed;
			}
		}
		
		//落下開始
		if (jumpUpSpeed_ < floatStandardNumber)
		{ 
			isFall_ = true;
		}
	}
	//ジャンプを完全に終了
	else if (jumpCount_ >= maxJumpCount_)
	{
		isJumpCount_	= false;
		jumpCount_		= standardNumber;
		if (jumpUpSpeed_ > floatStandardNumber)
		{
			jumpUpSpeed_ = floatStandardNumber;
			isFall_ = true;
		}
		gravity_		= jumpUpSpeed_ * -1;	//落下量をそのまま重力が引き継ぐ
		isSuperJump_	= false;
	}
}

//無敵時間
void Player::invincibleTime_(Player* player, Bird* bird[],Effect* effect, Shield* shield)
{
	//無敵中は当たり判定に入らない
	if (!isInvincible_)
	{
		isInvincible_ = hit(player, bird, effect);

		//スーパージャンプした瞬間はダメージを無効にする
		if (isSuperJump_)
		{
			isInvincible_ = false;
		}

		if (isInvincible_)
		{
			//シールドの効果が残ってたらダメージを無効化する
			if (shield->GeteffectCount_() > standardNumber)
			{
				isInvincible_ = false;
			}
			else
			{
				//ダメージを受けてスタミナが減る
				stamina_ += damageStamina;
				PlaySoundMem(damageSound_, DX_PLAYTYPE_BACK, TRUE);

				//ジャンプ上昇を中断
				if (jumpUpSpeed_ > floatStandardNumber)
				{
					jumpUpSpeed_ = floatStandardNumber;
				}
			}
		}
	}

	//無敵時間をカウント
	if (isInvincible_)
	{
		if (invincibleCount_ < maxInvincibleCount)
		{
			++invincibleCount_;
		}
		else
		{
   			invincibleCount_ = standardNumber;
			isInvincible_ = false;
		}
	}

	//効果量を減らす
	shield->decreseEffectCount_();
}

//描画
void Player::Draw_(Rocket* rocket)
{
	if (isInvincible_ && invincibleCount_ % 2 == 0)
	{
		//無敵中に点滅させる
	}
	else
	{
		if (rocket->GeteffectCount_() == standardNumber)
		{
			MV1DrawModel(modelHandle_);
		}
	}
}

//ジャンプ貯める
void Player::chargeJump_(Effect* effect, ChargeEffect* chargeEffect)
{
	//スペースを押してるかつスタミナがあればじゃんぷをためる
	if (CheckHitKey(KEY_INPUT_SPACE) && stamina_ < maxStamina)
	{
		stamina_				+= consumingStamina;
		consumingStaminaCount_	+= consumingStamina;

		//落ちてるときにためてたら落下量に押し戻しを付与
		if (isFall_)
		{
			position_.y += 0.5;
		}

		if (consumingStaminaCount_ > maxStamina)
		{
			consumingStaminaCount_ = maxStamina;
		}
		//スタミナを一定量消費しないとジャンプ出来ない
		if (consumingStaminaCount_ > 8)
		{
			if (canStartChargingSound_)
			{
				//PlaySoundMem(chargingSound_, DX_PLAYTYPE_LOOP, TRUE);
				canStartChargingSound_ = false;
			}

			effect->UpdateCharge_(this);
			//chargeEffect->Update_(this);
			maxNormalJumpCount_		+= addMaxNormalJumpCount;
			canStartJump_			= true;
		}
	}
}

//横移動
void Player::moveX_()
{
	// 右を押していたら右に進む
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		xSubtractSpeed_ = floatStandardNumber;
		xAddSpeed_ += velocity;
		if (xAddSpeed_ > maxXSpeed)
		{
			xAddSpeed_ = maxXSpeed;
		}
		position_.x += xAddSpeed_;
		isFacingRight = true;
	}
	// 左を押していたら左に進む
	else if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		xAddSpeed_ = floatStandardNumber;
		xSubtractSpeed_ += velocity;
		if (xSubtractSpeed_ > maxXSpeed)
		{
			xSubtractSpeed_ = maxXSpeed;
		}
		position_.x -= xSubtractSpeed_;
		isFacingRight = false;
	}
	else
	{
		xAddSpeed_ = floatStandardNumber;
		xSubtractSpeed_ = floatStandardNumber;
	}
}

//どっち向き
void Player::facing_()
{
	//どっちを向くか
	if (isFacingRight)
	{
		MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, 270.00f * DX_PI_F / 180.00f, floatStandardNumber));
	}
	else
	{
		MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, 90.00f * DX_PI_F / 180.00f, floatStandardNumber));
	}
}

//押し戻し
void Player::pushBack_()
{
	//押し戻し処理
	if (position_.x > playerXMAX)
	{
		position_.x = playerXMAX;
	}
	if (position_.x < playerXMIN)
	{
		position_.x = playerXMIN;
	}
	if (position_.y < floatStandardNumber)
	{
		position_.y = floatStandardNumber;
		gravity_	= floatStandardNumber;
		isFall_		= false;
	}
}

//ロケット乗車中
void Player::ridingRocket_()
{
	position_.y		+= ridingRocketSpeed;
	isFall_			= false;
	gravity_		= floatStandardNumber;
	jumpUpSpeed_	= floatStandardNumber;
}

//スタミナ回復
void Player::healStamina_()
{
	++staminaCount_;
	if (staminaCount_ == maxStaminaCount_)
	{
		staminaCount_ = maxStaminaCount_;
	}

	if (staminaCount_ % 3 == 0 /*&& !canStartJump_*/)
	{
		--stamina_;

		//最大を超えない
		if (stamina_ < standardNumber)
		{
			stamina_ = standardNumber;
		}
		if (stamina_ > maxStamina)
		{
			stamina_ = maxStamina;
		}
	}
}

//スタミナ全回復
void Player::allHealStamina_(CupCake* cupCake)
{
	if (cupCake->GetisHealingStamina_())
	{
		stamina_ = standardNumber;
		cupCake->cannotHealAllStamina_();
	}
}

//誘拐される
void Player::abducted_(UFO* ufo)
{
	if (ufo->GetcanAbduct_())
	{
		//プレイヤーのｙ座標をランダムな場所に飛ばす
		position_.y = GetRand(abducteingRange);
		ufo->cannotAbduct_();
	}
}