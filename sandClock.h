#pragma once
#include"item.h"

class SandClock:public Item
{
public:
	SandClock();
	~SandClock();

	void cannotAddTimer_();	//�^�C�}�[�𑝂₹�Ȃ�����

	bool	GetisAddTimer_()const { return isAddTimer_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	void itemEffect_()override;					//�A�C�e�����ʁi�I�[�o�[���C�h)

	bool isAddTimer_;

	const int   sandClockSpawn_		= 70;		//�o���m��
	const float speed_				= -1.0f;	//�X�s�[�h
	const float spawnPositionY_		= 120.0f;	//�X�|�[���|�W�V����
	const float sandClockHitboxX_	= 10.0f;	//�q�b�g�{�b�N�X��
	const float sandClockHitboxY_	= 10.0f;	//�q�b�g�{�b�N�Xy
};