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

//�R���X�g���N�^
Player::Player()
{
	// �R�c���f���̓ǂݍ���
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

//�f�X�g���N�^
Player::~Player()
{
	MV1DeleteModel(modelHandle_);
	DeleteSoundMem(superJumpSound_);
	DeleteSoundMem(jumpSound_);
	DeleteSoundMem(damageSound_);
}

//������
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

//�X�V
void Player::Update_(Animation* animation, Player* player, Effect* effect,Wing* wing,Rocket* rocket,CupCake* cupCake,UFO* ufo,ChargeEffect* chargeEffect)
{
	//���ړ�
	moveX_();

	//�ǂ�������
	facing_();

	//�W�����v�֐����Ăяo��
	jump_(animation,this,effect,wing);

	//�W�����v���߂�֐����Ăяo��
	chargeJump_(effect,chargeEffect);

	//�X�^�~�i��
	healStamina_();

	//�X�^�~�i�S��
	allHealStamina_(cupCake);
	
	//�����߂�
	pushBack_();

	//�O�ՃG�t�F�N�g
	effect->UpdateTrajectory_(this);

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(modelHandle_, position_);

	//���P�b�g
	rocket->decreseEffectCount_();
	rocket->ride_(this);

	//ufo�ɗU�������
	abducted_(ufo);
}

//�W�����v
void Player::jump_(Animation* animation, Player* player, Effect* effect, Wing* wing)
{
	//�X�y�[�X���͂Ȃ��ăW�����v
	if (CheckHitKey(KEY_INPUT_SPACE) == false && canStartJump_|| isSuperJump_)
	{
		if (!isPrevSpace_)
		{
			//���O����
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

	//�W�����v���֐����Ăяo��
	nowJump_();

	//�W�����v���Ă��Ȃ����͏d�͂�����
	if (!isJumpCount_ && position_.y != floatStandardNumber)
	{
		if (maxGravityVelocity > gravity_)
		{
			gravity_ += gravityVelocity;
		}
		position_.y -= gravity_;
	}
}

//�W�����v�؂�ւ�
void Player::changeJumpType(Player* player, Bird* bird[], Effect* effect)
{
	//�ʏ�W�����v�ƃX�[�p�[�W�����v�̐؂�ւ�
	if (!isSuperJump_)
	{
		isSuperJump_ = superJump(this, bird,effect);
	}
}

//�W�����v���֐�
void Player::nowJump_()
{
	//�J�E���g�����ɂȂ�܂ł̓W�����v�𑱂���
	if (jumpCount_ < maxJumpCount_ && isJumpCount_)
	{
		position_.y += jumpUpSpeed_;
		++jumpCount_;
		
		if (jumpCount_ > maxJumpCount_ / 5)
		{
			//�ő嗎�����x���d�͂������ĂȂ�������d�͉����x�𑫂�
			if (maxGravityVelocity > gravity_)
			{
				gravity_ += gravityVelocity;
			}
			jumpUpSpeed_ -= gravity_;

			//�ŏ��W�����v�X�s�[�h��菬�����Ȃ����猳�ɖ߂�
			if (minimumJumpUPSpeed > jumpUpSpeed_)
			{
				jumpUpSpeed_ = minimumJumpUPSpeed;
			}
		}
		
		//�����J�n
		if (jumpUpSpeed_ < floatStandardNumber)
		{ 
			isFall_ = true;
		}
	}
	//�W�����v�����S�ɏI��
	else if (jumpCount_ >= maxJumpCount_)
	{
		isJumpCount_	= false;
		jumpCount_		= standardNumber;
		if (jumpUpSpeed_ > floatStandardNumber)
		{
			jumpUpSpeed_ = floatStandardNumber;
			isFall_ = true;
		}
		gravity_		= jumpUpSpeed_ * -1;	//�����ʂ����̂܂܏d�͂������p��
		isSuperJump_	= false;
	}
}

//���G����
void Player::invincibleTime_(Player* player, Bird* bird[],Effect* effect, Shield* shield)
{
	//���G���͓����蔻��ɓ���Ȃ�
	if (!isInvincible_)
	{
		isInvincible_ = hit(player, bird, effect);

		//�X�[�p�[�W�����v�����u�Ԃ̓_���[�W�𖳌��ɂ���
		if (isSuperJump_)
		{
			isInvincible_ = false;
		}

		if (isInvincible_)
		{
			//�V�[���h�̌��ʂ��c���Ă���_���[�W�𖳌�������
			if (shield->GeteffectCount_() > standardNumber)
			{
				isInvincible_ = false;
			}
			else
			{
				//�_���[�W���󂯂ăX�^�~�i������
				stamina_ += damageStamina;
				PlaySoundMem(damageSound_, DX_PLAYTYPE_BACK, TRUE);

				//�W�����v�㏸�𒆒f
				if (jumpUpSpeed_ > floatStandardNumber)
				{
					jumpUpSpeed_ = floatStandardNumber;
				}
			}
		}
	}

	//���G���Ԃ��J�E���g
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

	//���ʗʂ����炷
	shield->decreseEffectCount_();
}

//�`��
void Player::Draw_(Rocket* rocket)
{
	if (isInvincible_ && invincibleCount_ % 2 == 0)
	{
		//���G���ɓ_�ł�����
	}
	else
	{
		if (rocket->GeteffectCount_() == standardNumber)
		{
			MV1DrawModel(modelHandle_);
		}
	}
}

//�W�����v���߂�
void Player::chargeJump_(Effect* effect, ChargeEffect* chargeEffect)
{
	//�X�y�[�X�������Ă邩�X�^�~�i������΂����Ղ����߂�
	if (CheckHitKey(KEY_INPUT_SPACE) && stamina_ < maxStamina)
	{
		stamina_				+= consumingStamina;
		consumingStaminaCount_	+= consumingStamina;

		//�����Ă�Ƃ��ɂ��߂Ă��痎���ʂɉ����߂���t�^
		if (isFall_)
		{
			position_.y += 0.5;
		}

		if (consumingStaminaCount_ > maxStamina)
		{
			consumingStaminaCount_ = maxStamina;
		}
		//�X�^�~�i�����ʏ���Ȃ��ƃW�����v�o���Ȃ�
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

//���ړ�
void Player::moveX_()
{
	// �E�������Ă�����E�ɐi��
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
	// ���������Ă����獶�ɐi��
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

//�ǂ�������
void Player::facing_()
{
	//�ǂ�����������
	if (isFacingRight)
	{
		MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, 270.00f * DX_PI_F / 180.00f, floatStandardNumber));
	}
	else
	{
		MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, 90.00f * DX_PI_F / 180.00f, floatStandardNumber));
	}
}

//�����߂�
void Player::pushBack_()
{
	//�����߂�����
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

//���P�b�g��Ԓ�
void Player::ridingRocket_()
{
	position_.y		+= ridingRocketSpeed;
	isFall_			= false;
	gravity_		= floatStandardNumber;
	jumpUpSpeed_	= floatStandardNumber;
}

//�X�^�~�i��
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

		//�ő�𒴂��Ȃ�
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

//�X�^�~�i�S��
void Player::allHealStamina_(CupCake* cupCake)
{
	if (cupCake->GetisHealingStamina_())
	{
		stamina_ = standardNumber;
		cupCake->cannotHealAllStamina_();
	}
}

//�U�������
void Player::abducted_(UFO* ufo)
{
	if (ufo->GetcanAbduct_())
	{
		//�v���C���[�̂����W�������_���ȏꏊ�ɔ�΂�
		position_.y = GetRand(abducteingRange);
		ufo->cannotAbduct_();
	}
}