#pragma once
#include"item.h"

//�q�N���X(�H)
class Wing :public Item
{
public:
	Wing();
	~Wing();

	int		GeteffectCount_()const { return effectCount_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	const int   wingSpawn			= 45;		//�H�o���m��
	const float wingSpeedX_			= 2.0f;		//�H�X�s�[�h
	const float wingSpeedY_			= 3.0f;		//�H�X�s�[�h
	const float spawnPositionX_		= -150.0f;	//�X�|�[���|�W�V����
	const float wingHitboxX_		= 15.0f;	//�H�q�b�g�{�b�N�X��
	const float wingHitboxY_		= 10.0f;	//�H�q�b�g�{�b�N�Xy
	const int   maxWingEffectCount_ = 2;		//�ő�G�t�F�N�g�J�E���g
};