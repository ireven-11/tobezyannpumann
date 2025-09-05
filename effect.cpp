#include"DxLib.h"
#include"common.h"
#include"effect.h"
#include"EffekseerForDXLib.h"
#include"bird.h"
#include"player.h"
#include"item.h"

//�R���X�g���N�^
Effect::Effect()
{
	//�G�t�F�N�g�ǂݍ���
	superJumpEffect_			= LoadEffekseerEffect("effect/superJump.efkefc");
	itemGetEffect_				= LoadEffekseerEffect("effect/getItem.efkefc");
	trajectoryEffect_			= LoadEffekseerEffect("effect/trajectory2.efkefc");
	chargeEffect_				= LoadEffekseerEffect("effect/charge.efkefc");
	shine_						= LoadEffekseerEffect("effect/shine.efkefc");
	
	//���W������
	superJumpEffectPosition_	= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	itemGetEffectPosition_		= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	trajectoryEffectPosition_	= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	chargeEffectPosition_		= VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
	
	//�Đ����n���h��������
	playingSuperJumpEffect_		= standardNumber;
	playingItemGetEffect_		= standardNumber;
	playingTrajectoryEffect_	= standardNumber;
	playingChargeEffect_		= standardNumber;
	playingShine_				= standardNumber;
	
	trajectoryCount_			= standardNumber;
	shineCount_					= standardNumber;
}

//�f�X�g���N�^
Effect::~Effect()
{
	DeleteEffekseerEffect(superJumpEffect_);
	DeleteEffekseerEffect(itemGetEffect_);
	DeleteEffekseerEffect(trajectoryEffect_);
	DeleteEffekseerEffect(chargeEffect_);
}

//�X�[�p�[�W�����v�G�t�F�N�g�X�V
void Effect::UpdateSuperJump_(Bird* bird[], int& i)
{
	//�X�[�p�[�W�����v�G�t�F�N�g���Đ�
	playingSuperJumpEffect_ = PlayEffekseer3DEffect(superJumpEffect_);

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
	SetScalePlayingEffekseer3DEffect(playingSuperJumpEffect_, 0.5f, 0.5f, 0.5f);

	//�Đ����G�t�F�N�g�̊p�x��ݒ肷��(������playing�n���h���Ƃ������̊p�x)
	SetRotationPlayingEffekseer3DEffect(playingSuperJumpEffect_, 0, 0, 0);

	//2d�G�t�F�N�g�̍Đ����x��ݒ�(������playing�n���h����float�^�̍Đ����x)
	SetSpeedPlayingEffekseer3DEffect(playingSuperJumpEffect_, superJumpEffectPlayingSpeed);
	
	superJumpEffectPosition_.x = bird[i]->Getposition_().x;
	superJumpEffectPosition_.y = bird[i]->Getposition_().y + 5;

	//���W���Z�b�g
	SetPosPlayingEffekseer3DEffect(playingSuperJumpEffect_, superJumpEffectPosition_.x, superJumpEffectPosition_.y, 0);
}

//�`��
void Effect::Draw_()
{
	//�G�t�F�N�g���X�V
	UpdateEffekseer3D();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g�S�Ă�`�悷��B
	DrawEffekseer3D();
}

//�A�C�e���Q�b�g�X�V
void Effect::UpdateItemGet_(Player* player)
{
	playingItemGetEffect_ = PlayEffekseer3DEffect(itemGetEffect_);

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
	SetScalePlayingEffekseer3DEffect(playingItemGetEffect_, 1.5f, 1.5f, 1.5f);

	//2d�G�t�F�N�g�̍Đ����x��ݒ�(������playing�n���h����float�^�̍Đ����x)
	SetSpeedPlayingEffekseer3DEffect(playingItemGetEffect_, itemGetEffectPlayingSpeed);

	itemGetEffectPosition_.x = player->Getposition_().x;
	itemGetEffectPosition_.y = player->Getposition_().y + 20;

	//���W���Z�b�g
	SetPosPlayingEffekseer3DEffect(playingItemGetEffect_, itemGetEffectPosition_.x, itemGetEffectPosition_.y, floatStandardNumber);
}

//�O�ՍX�V
void Effect::UpdateTrajectory_(Player* player)
{
	++trajectoryCount_;
	//�㏸���Ă���Ԃ����O�ՃG�t�F�N�g������
	if (player->GetjumpUpSpeed_() > floatStandardNumber && trajectoryCount_ % 2 == 0)
	{
		playingTrajectoryEffect_= PlayEffekseer3DEffect(trajectoryEffect_);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
		SetScalePlayingEffekseer3DEffect(playingTrajectoryEffect_, 1.5f, 1.5f, 1.5f);

		//2d�G�t�F�N�g�̍Đ����x��ݒ�(������playing�n���h����float�^�̍Đ����x)
		SetSpeedPlayingEffekseer3DEffect(playingTrajectoryEffect_, trajectoryEffectPlayingSpeed);

		trajectoryEffectPosition_.x = player->Getposition_().x;
		trajectoryEffectPosition_.y = player->Getposition_().y - 3;

		//���W���Z�b�g
		SetPosPlayingEffekseer3DEffect(playingTrajectoryEffect_, trajectoryEffectPosition_.x, trajectoryEffectPosition_.y, floatStandardNumber);
	}

	//�I�[�o�[�t���[�΍�
	if (trajectoryCount_ > 1000)
	{
		trajectoryCount_ = 0;
	}
}

//�`���[�W�G�t�F�N�g�X�V
void Effect::UpdateCharge_(Player* player)
{
	playingChargeEffect_ = PlayEffekseer3DEffect(chargeEffect_);

	// �G�t�F�N�g�̊g�嗦��ݒ肷��B
	// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
	SetScalePlayingEffekseer3DEffect(playingChargeEffect_, 5.0f, 1.5f, 3.0f);

	//2d�G�t�F�N�g�̍Đ����x��ݒ�(������playing�n���h����float�^�̍Đ����x)
	SetSpeedPlayingEffekseer3DEffect(playingChargeEffect_, chargeEffectPlayingSpeed);

	chargeEffectPosition_.x = player->Getposition_().x;
	chargeEffectPosition_.y = player->Getposition_().y;

	//���W���Z�b�g
	SetPosPlayingEffekseer3DEffect(playingChargeEffect_, chargeEffectPosition_.x, chargeEffectPosition_.y, floatStandardNumber);
}

//�L���L���X�V
void Effect::kirakira_(Item* item)
{
	if (shineCount_ % 100 == 0)
	{
		playingShine_ = PlayEffekseer3DEffect(shine_);

		// �G�t�F�N�g�̊g�嗦��ݒ肷��B
		// Effekseer�ō쐬�����G�t�F�N�g��2D�\���̏ꍇ�A���������邱�Ƃ��w�ǂȂ̂ŕK���g�傷��B
		SetScalePlayingEffekseer3DEffect(shine_, 5.0f, 5.0f, 5.0f);

		//2d�G�t�F�N�g�̍Đ����x��ݒ�(������playing�n���h����float�^�̍Đ����x)
		SetSpeedPlayingEffekseer3DEffect(shine_, shineSpeed);
	}

	//���W���Z�b�g
	SetPosPlayingEffekseer3DEffect(playingShine_, item->Getposition_().x, item->Getposition_().y + 5, floatStandardNumber);
}

//�L���L���J�E���g
void Effect::kirakiraCounter_()
{
	++shineCount_;
	//�I�[�o�[�t���[�΍�
	if (shineCount_ > 1000)
	{
		shineCount_ = standardNumber;
	}

}