#include"DxLib.h"
#include"common.h"
#include"effect.h"
#include"EffekseerForDXLib.h"
#include"bird.h"
#include"player.h"
#include"item.h"

//コンストラクタ
Effect::Effect()
{
	//エフェクト読み込み
	superJumpEffect_			= LoadEffekseerEffect("effect/superJump.efkefc");
	itemGetEffect_				= LoadEffekseerEffect("effect/getItem.efkefc");
	trajectoryEffect_			= LoadEffekseerEffect("effect/trajectory2.efkefc");
	chargeEffect_				= LoadEffekseerEffect("effect/charge.efkefc");
	shine_						= LoadEffekseerEffect("effect/shine.efkefc");
	
	//座標初期化
	superJumpEffectPosition_	= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	itemGetEffectPosition_		= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	trajectoryEffectPosition_	= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	chargeEffectPosition_		= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	
	//再生中ハンドル初期化
	playingSuperJumpEffect_		= standardNumber;
	playingItemGetEffect_		= standardNumber;
	playingTrajectoryEffect_	= standardNumber;
	playingChargeEffect_		= standardNumber;
	playingShine_				= standardNumber;
	
	trajectoryCount_			= standardNumber;
	shineCount_					= standardNumber;
}

//デストラクタ
Effect::~Effect()
{
	DeleteEffekseerEffect(superJumpEffect_);
	DeleteEffekseerEffect(itemGetEffect_);
	DeleteEffekseerEffect(trajectoryEffect_);
	DeleteEffekseerEffect(chargeEffect_);
}

//スーパージャンプエフェクト更新
void Effect::UpdateSuperJump_(Bird* bird[], int& i)
{
	//スーパージャンプエフェクトを再生
	playingSuperJumpEffect_ = PlayEffekseer3DEffect(superJumpEffect_);

	// エフェクトの拡大率を設定する。
	// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
	SetScalePlayingEffekseer3DEffect(playingSuperJumpEffect_, 0.5f, 0.5f, 0.5f);

	//再生中エフェクトの角度を設定する(引数はplayingハンドルとｘｙｚの角度)
	SetRotationPlayingEffekseer3DEffect(playingSuperJumpEffect_, 0, 0, 0);

	//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
	SetSpeedPlayingEffekseer3DEffect(playingSuperJumpEffect_, superJumpEffectPlayingSpeed);
	
	superJumpEffectPosition_.x = bird[i]->Getposition_().x;
	superJumpEffectPosition_.y = bird[i]->Getposition_().y + 5;

	//座標をセット
	SetPosPlayingEffekseer3DEffect(playingSuperJumpEffect_, superJumpEffectPosition_.x, superJumpEffectPosition_.y, 0);
}

//描画
void Effect::Draw_()
{
	//エフェクトを更新
	UpdateEffekseer3D();

	// Effekseerにより再生中のエフェクト全てを描画する。
	DrawEffekseer3D();
}

//アイテムゲット更新
void Effect::UpdateItemGet_(Player* player)
{
	playingItemGetEffect_ = PlayEffekseer3DEffect(itemGetEffect_);

	// エフェクトの拡大率を設定する。
	// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
	SetScalePlayingEffekseer3DEffect(playingItemGetEffect_, 1.5f, 1.5f, 1.5f);

	//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
	SetSpeedPlayingEffekseer3DEffect(playingItemGetEffect_, itemGetEffectPlayingSpeed);

	itemGetEffectPosition_.x = player->Getposition_().x;
	itemGetEffectPosition_.y = player->Getposition_().y + 20;

	//座標をセット
	SetPosPlayingEffekseer3DEffect(playingItemGetEffect_, itemGetEffectPosition_.x, itemGetEffectPosition_.y, floatStandardNumber);
}

//軌跡更新
void Effect::UpdateTrajectory_(Player* player)
{
	++trajectoryCount_;
	//上昇している間だけ軌跡エフェクトをだす
	if (player->GetjumpUpSpeed_() > floatStandardNumber && trajectoryCount_ % 2 == 0)
	{
		playingTrajectoryEffect_= PlayEffekseer3DEffect(trajectoryEffect_);

		// エフェクトの拡大率を設定する。
		// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
		SetScalePlayingEffekseer3DEffect(playingTrajectoryEffect_, 1.5f, 1.5f, 1.5f);

		//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
		SetSpeedPlayingEffekseer3DEffect(playingTrajectoryEffect_, trajectoryEffectPlayingSpeed);

		trajectoryEffectPosition_.x = player->Getposition_().x;
		trajectoryEffectPosition_.y = player->Getposition_().y - 3;

		//座標をセット
		SetPosPlayingEffekseer3DEffect(playingTrajectoryEffect_, trajectoryEffectPosition_.x, trajectoryEffectPosition_.y, floatStandardNumber);
	}

	//オーバーフロー対策
	if (trajectoryCount_ > 1000)
	{
		trajectoryCount_ = 0;
	}
}

//チャージエフェクト更新
void Effect::UpdateCharge_(Player* player)
{
	playingChargeEffect_ = PlayEffekseer3DEffect(chargeEffect_);

	// エフェクトの拡大率を設定する。
	// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
	SetScalePlayingEffekseer3DEffect(playingChargeEffect_, 5.0f, 1.5f, 3.0f);

	//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
	SetSpeedPlayingEffekseer3DEffect(playingChargeEffect_, chargeEffectPlayingSpeed);

	chargeEffectPosition_.x = player->Getposition_().x;
	chargeEffectPosition_.y = player->Getposition_().y;

	//座標をセット
	SetPosPlayingEffekseer3DEffect(playingChargeEffect_, chargeEffectPosition_.x, chargeEffectPosition_.y, floatStandardNumber);
}

//キラキラ更新
void Effect::kirakira_(Item* item)
{
	if (shineCount_ % 100 == 0)
	{
		playingShine_ = PlayEffekseer3DEffect(shine_);

		// エフェクトの拡大率を設定する。
		// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
		SetScalePlayingEffekseer3DEffect(shine_, 5.0f, 5.0f, 5.0f);

		//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
		SetSpeedPlayingEffekseer3DEffect(shine_, shineSpeed);
	}

	//座標をセット
	SetPosPlayingEffekseer3DEffect(playingShine_, item->Getposition_().x, item->Getposition_().y + 5, floatStandardNumber);
}

//キラキラカウント
void Effect::kirakiraCounter_()
{
	++shineCount_;
	//オーバーフロー対策
	if (shineCount_ > 1000)
	{
		shineCount_ = standardNumber;
	}

}