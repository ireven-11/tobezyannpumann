#pragma once
#include"item.h"

//�q�N���X(��)
class Shield :public Item
{
public:
	Shield();
	~Shield();

	int		GeteffectCount_()const { return effectCount_; }
	bool	GetcanProtectDamage_()const { return canProtectDamage_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

	void decreseEffectCount_() override;//�A�C�e���J�E���g����
	void DrawEffectIcon_() override;	//���ʃA�C�R���`��

private:
	void itemEffect_() override;					//�A�C�e���̌���(�I�[�o�[���C�h)

	const int    shieldSpawn = 100;		//�V�[���h�o���m��
	const float  shieldSpeed = -1.0f;	//�V�[���h�X�s�[�h
	const int	 spawnPositionY_ = 70.0f;	//�X�|�[���|�W�V����Y
	const float  shieldHitboxX_ = 10.0f;	//�V�[���h�q�b�g�{�b�N�X��
	const float  shieldHitboxY_ = 15.0f;	//�V�[���h�q�b�g�{�b�N�Xy
	const int    maxShieldEffectCount_ = 250;		//�ő�G�t�F�N�g�J�E���g
	const int    maxProtectDamageCount_ = 10;		//�_���[�W�h���ő�J�E���g

	bool		canProtectDamage_;					//�_���[�W�h���邩�t���O
};