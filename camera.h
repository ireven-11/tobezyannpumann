#pragma once

const int	maxFallCount		= 10;		//�ő嗎���J�E���g
const int	minimumFallCount	= -10;		//�ŏ������J�E���g
const float	initZ				= -75.00f;	//�J��������Z
const float initY				= 15.00f;	//�J��������Y
const float initTargetY			= 10.00f;	//�^�[�Q�b�g����Y
const int	subFallCount		= 3;		//�J���������������x		

class Player;

class Camera
{
public:
	Camera();						//�R���X�g���N�^
	~Camera();						//�f�X�g���N�^

	void Update_(Player* player);	//�X�V

private:
	VECTOR position_;		//�J�����|�W�V����
	VECTOR targetPosition_;	//�J�����̃^�[�Q�b�g�|�W�V����
	int	   fallCount_ = 0;	//�����J�E���g
};