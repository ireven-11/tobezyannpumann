#pragma once

//����
//�G�̌����ڂ����邩��Ɉ������Ȍ����ڂɂ��邱�ƂœG���Ƃ킩��₷�������F�N���{�[

const int	maxBirdNumber			= 100;		//���̍ő吔
const float	resetPosition			= 90.00f;	//���Z�b�g�|�W�V����
const float intervalY				= 130.00f;	//���ƒ��̊Ԋu
const float standardSpeed			= 0.15f;	//��X�s�[�h
const int	tutorialLeftBirdNumber	= 4;		//�ŏ���4�͍̂�����o�Ă���
const int	tutorialRightBirdNumber = 8;		//����4�͉̂E����o�Ă���
const int	drawUpRange				= 50;		//���̕`��͈�(�v���C���[��������ɂ���Ƃ�)
const int	drawDownRange			= 85;		//���̕`��͈�(�v���C���[������艺�ɂ���Ƃ�)

class Player;

class Bird
{
public:
	Bird(int& i);		//�R���X�g���N�^
	~Bird();			//�f�X�g���N�^

	void Update_(int& i);				//�X�V
	void Draw_(Player* player, int& i);	//�`��
	void Init_(int& i);					//������

	VECTOR Getposition_()const { return position_; }
	int	   GetmodelHandle_()const { return modelHandle_; }

private:
	int	   modelHandle_;			//���f���n���h��
	VECTOR position_;				//�|�W�V����
	bool   isFromRight_ = false;	//�E���炭�邩�t���O
	float  speed_		= 0.30f;	//�X�s�[�h
	
	void InitPosition_(int& i);		//���W������
	void InitMove_(int& i);			//����������
	void rotation_(int& i);			//������]				
};