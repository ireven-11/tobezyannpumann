#pragma once

const float transitionPositionX = 0.0f;	//�g�����W�V����x���W
const float transitionPositionY = 0.0f;	//�g�����W�V���������W
const int	maxTransitionCount	= 45;	//�ő�g�����W�V�����J�E���g

class Transition
{
public:
	Transition();
	~Transition();

	void Init();	//������
	void Update();	//�X�V
	void Reset();	//���Z�b�g

	int GettransitionCount_()const { return transitionCount_; }
	int GetleftFlipHandle_()const { return leftFlipHandle_; }
	int GetrightFlipHandle_()const { return rightFlipHandle_; }
	int GetleftLongFlipHandle_()const { return leftLongFlipHandle_; }
	int GetrightLongFlipHandle_()const { return rightLongFlipHandle_; }

private:
	int   handle_;				//�g�����W�V�����n���h��
	int   transitionCount_;     //�g�����W�V�����J�E���g
	bool  canPlayTransition_;   //�g�����W�V�������Ȃ����邩�t���O
	int	  leftFlipHandle_;		//�߂���g�����W�V�����i��)
	int	  rightFlipHandle_;		//�߂���g�����W�V�����i�E)
	int	  leftLongFlipHandle_;	//�����߂���g�����W�V�����i��)
	int	  rightLongFlipHandle_;	//�����߂���g�����W�V�����i�E)
};