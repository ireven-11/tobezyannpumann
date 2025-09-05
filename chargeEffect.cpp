#include"DxLib.h"
#include"common.h"
#include"chargeEffect.h"
#include"EffekseerForDXLib.h"
#include"player.h"


ChargeEffect::ChargeEffect()
{
	handle_ = LoadEffekseerEffect("effect/charge.efkefc");
	position_ = VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	playingHandle_ = standardNumber;
	count_ = standardNumber;
	canStartCount_ = false;
	canStart_	   = true;
}

ChargeEffect::~ChargeEffect()
{
	DeleteEffekseerEffect(handle_);
}

void ChargeEffect::Draw_(Player* player)
{
	SetPosPlayingEffekseer3DEffect(playingHandle_, player->Getposition_().x, player->Getposition_().y, floatStandardNumber);

	//エフェクトを更新
	UpdateEffekseer3D();
	UpdateCount_();
	
	DrawEffekseer3D_Draw(playingHandle_);
}

void ChargeEffect::Update_(Player* player)
{
	if (canStart_)
	{
		playingHandle_ = PlayEffekseer3DEffect(handle_);

		// エフェクトの拡大率を設定する。
		// Effekseerで作成したエフェクトは2D表示の場合、小さすぎることが殆どなので必ず拡大する。
		SetScalePlayingEffekseer3DEffect(playingHandle_, 3.0f, 1.5f, 3.0f);

		//2dエフェクトの再生速度を設定(引数はplayingハンドルとfloat型の再生速度)
		SetSpeedPlayingEffekseer3DEffect(playingHandle_, 1.0);

		canStart_ = false;
		canStartCount_ = true;

		DrawEffekseer2D_Begin();
	}
}

void ChargeEffect::UpdateCount_()
{
	if (canStartCount_)
	{
		++count_;

		if (count_ > maxCount_)
		{
			DrawEffekseer2D_End();
			canStartCount_ = false;
			canStart_ = true;
		}
	}
}