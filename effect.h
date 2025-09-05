#pragma once

const float superJumpEffectPlayingSpeed		= 6.0f;	//�X�[�p�[�W�����v�G�t�F�N�g�̍Đ����x
const float jumpEffectPlayingSpeed			= 3.0f;	//�W�����v�G�t�F�N�g�̍Đ����x
const float itemGetEffectPlayingSpeed		= 1.5f;	//�A�C�e���Q�b�g�G�t�F�N�g�̍Đ����x
const float trajectoryEffectPlayingSpeed	= 5.0f;	//�O�ՃX�s�[�h
const float chargeEffectPlayingSpeed		= 55.0f;//�`���[�W�G�t�F�N�g�̍Đ����x
const float shineSpeed						= 395.0f;//�L���L���X�s�[�h

class Bird;
class Player;
class Item;

class Effect
{
public:
	Effect();
	~Effect();

	void UpdateSuperJump_(Bird* bird[], int& i);//�X�[�p�[�W�����v�X�V
	void Draw_();								//�`��
	void UpdateItemGet_(Player* player);		//�A�C�e���Q�b�g�X�V
	void UpdateTrajectory_(Player* player);		//�O�ՍX�V
	void UpdateCharge_(Player* player);			//�`���[�W�X�V
	void kirakira_(Item* item);					//�L���L���X�V
	void kirakiraCounter_();					//�L���L���J�E���^�[

private:
	int    superJumpEffect_;			//�X�[�p�[�W�����v�G�t�F�N�g
	VECTOR superJumpEffectPosition_;	//�X�[�p�[�W�����v�G�t�F�N�g�|�W�V����
	int    playingSuperJumpEffect_;		//�Đ����n���h���i�X�[�p�[�W�����v�j
	VECTOR itemGetEffectPosition_;		//�A�C�e���Q�b�g���W
	int    itemGetEffect_;				//�A�C�e���Q�b�g�G�t�F�N�g
	int    playingItemGetEffect_;		//�Đ����n���h��(�A�C�e���Q�b�g)
	int	   trajectoryEffect_;			//�O�ՃG�t�F�N�g
	VECTOR trajectoryEffectPosition_;	//�O�ՃG�t�F�N�g���W
	int	   playingTrajectoryEffect_;	//�Đ����n���h��(�O��)
	int    trajectoryCount_;			//�O�ՃJ�E���g
	int	   chargeEffect_;				//�`���[�W�G�t�F�N�g
	VECTOR chargeEffectPosition_;		//���W
	int	   playingChargeEffect_;		//�Đ����n���h��
	int	   shine_;						//�L���L��
	int    shineCount_;					//�J�E���g
	int	   playingShine_;				//�v���C�n���h��
};
