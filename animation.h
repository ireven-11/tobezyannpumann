#pragma once

const int		maxAnimationNumber				= 2;	//�A�j���[�V�����ő吔
const int		jumpAnimationFirstHalf			= 50;	//�W�����v�A�j���[�V�����O��
const double	jumpAnimationSpeedFirstHalf		= 5.0;	//�W�����v�A�j���[�V�������x�O��
const double	jumpAnimationSpeedSecondHalf	= 1.0;	//�W�����v�A�j���[�V�������x�㔼
const double	fallAnimationSpeed				= 2.0;	//�����A�j���[�V�������x
const int		flyingAnimationSpeed			= 1.0f;	//��ԃA�j���[�V�����X�s�[�h

class Player;
class Bird;

class Animation
{
public:
	Animation(Player* player, Bird* bird[]);
	~Animation();

	void Update(Player* player);				//�X�V
	void jumpReset_();							//�W�����v���Z�b�g
	void Init_(Player* player);					//������
	void UpdateFlying_(Bird* bird[]);			//��ԍX�V
	void Delete_(Player* player, Bird* bird[]);	//�f�X�g���N�^�̑���i������n���Ȃ�����j

private:
	int   animationHandle_[3];		//�A�j���[�V�����n���h��
	int   jumpAnimation_;			//�W�����v�A�j���[�V����
	int	  fallAnimation_;			//�����A�j���[�V����
	float jumpTotalTime_;			//�W�����v�A�j���[�V����������
	float jumpNowTime_;				//�W�����v�A�j���[�V�����Đ�����
	float fallTotalTime_;			//�����A�j���[�V����������
	float fallNowTime_;				//�����A�j���[�V�����Đ�����
	bool  isPlayingJumpAnimation_;	//�W�����v�A�j���[�V�������Ȃ���Ă��邩
	bool  isPlayingFallAnimation_;	//�����A�j���[�V����������Ă��邩
	int   flyingAnimation_;			//��ԃA�j���[�V����
	float flyingTotalTime_;			//��ԑ�����
	float flyingNowTime_;			//��ԍĐ�����
	float saveAnimation_;			//�A�j���[�V�����ۑ�
	bool  canAddSaveAnimation_;		//�ۑ��A�j���[�V�������Z�ł��邩
	bool  isInitOneTime_;			//��񂾂��������t���O
};

