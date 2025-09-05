#pragma once
#include"item.h"

const int abducteingRange = 5000;	//�U���͈�

class UFO:public Item
{
public:
	UFO();
	~UFO();

	void cannotAbduct_();	//�U���ł��Ȃ�

	bool	GetcanAbduct_()const { return canAbduct_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;				//�A�C�e�����ʁi�I�[�o�[���C�h)

	bool canAbduct_;	//�U���ł��邩�t���O

	const int   ufoSpawn_		= 25;		//�o���m��
	const float ufoSpeedX_		= 2.0f;		//�X�s�[�h
	const float ufoSpeedY_		= 3.0f;		//�X�s�[�h
	const float spawnPositionX_ = -145.0f;	//�X�|�[���|�W�V����
	const float ufoHitboxX_		= 20.0f;	//�q�b�g�{�b�N�X��
	const float ufoHitboxY_		= 10.0f;	//�q�b�g�{�b�N�Xy
};