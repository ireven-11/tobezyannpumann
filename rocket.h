#pragma once
#include"item.h"

class Player;

//�q�N���X(���P�b�g)
class Rocket :public Item
{
public:
	Rocket();
	~Rocket();

	void ride_(Player* player);

	int		GeteffectCount_()const { return effectCount_; }
	int		GetmodelHandle_()const { return modelHandle_; }
	bool	GetonDictionary_()const { return onDictionary_; }

private:
	const int   rocketSpawn = 10;		//���P�b�g�o���m��
	const float rocketSpeed = 5.0f;		//���P�b�g�X�s�[�h
	const float spawnPositionY_ = -100.0f;	//�X�|�[���|�W�V����
	const float rocketHitboxX_ = 5.0f;		//���P�b�g�q�b�g�{�b�N�X��
	const float rocketHitboxY_ = 5.0f;		//���P�b�g�q�b�g�{�b�N�Xy
	const int	maxRocketEffectCount_ = 100;		//�ő�l�G�t�F�N�g�J�E���g
};