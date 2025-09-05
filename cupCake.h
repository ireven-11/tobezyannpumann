#pragma once
#include"item.h"

//�J�b�v�P�[�L
class CupCake:public Item
{
public:
	CupCake();
	~CupCake();

	void cannotHealAllStamina_();	

	bool	GetisHealingStamina_()const { return isHealingAllStamin_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;				//�A�C�e�����ʁi�I�[�o�[���C�h)

	bool isHealingAllStamin_;				//�X�^�~�i���񕜂��邩
	const int   cupCakeSpawn_	= 60;		//�o���m��
	const float speed_			= -1.0f;	//�X�s�[�h
	const float spawnPositionY_ = 60.0f;	//�X�|�[���|�W�V����
	const float cupCakeHitboxX_	= 10.0f;	//�q�b�g�{�b�N�X��
	const float cupCakeHitboxY_	= 10.0f;	//�q�b�g�{�b�N�Xy
};