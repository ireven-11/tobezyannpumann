#pragma once

const float  maxJumpSpeed			= 2.5f;		//�W�����v�ő呬�x
const float  velocity				= 0.30f;	//�����x
const float  maxXSpeed				= 2.50f;	//�ő�l�ړ���
const float  gravityVelocity		= 0.10f;	//�d�͉����x
const float  maxGravityVelocity		= 3.00f;	//�ő�d�͉����x
const int	 maxInvincibleCount		= 120;		//�ő喳�G�J�E���g
const double consumingStamina		= 1.0;		//����X�^�~�i
const float  maxSuperJumpCount		= 250.00f;	//�X�[�p�[�W�����v�ő�J�E���g
const float  playerXMIN				= -65.00f;	//�v���C���[�̂����W�ŏ��l
const float  playerXMAX				= 65.00f;	//�v���C���[�̂����W�ő�l
const int	 maxStamina				= 100;		//�X�^�~�i�ő�l
const double damageStamina			= 20.00;	//�_���[�W���󂯂��Ƃ��̏���X�^�~�i
const int	 addMaxNormalJumpCount	= 5;		//�ő�m�[�}���W�����v�J�E���g���Z��
const float  ridingRocketSpeed		= 10.0f;	//��Ԓ��̃��P�b�g�X�s�[�h
const int    maxStaminaCount_		= 1000;		//�ő�X�^�~�i�J�E���g
const float  minimumJumpUPSpeed		= -2.00f;	//�ŏ��W�����v���x

class Bird;
class Animation;
class Effect;
class Shield;
class Wing;
class Rocket;
class CupCake;
class UFO;
class ChargeEffect;

class Player
{
public:
	Player();																													//�R���X�g���N�^
	~Player();																													//�f�X�g���N�^

	void Init_();																												//������
	void Update_(Animation* animation, Player* player, Effect* effect, Wing* wing, Rocket* rocket, CupCake* cupCake, UFO* ufo,
		ChargeEffect* chargeEffect);	//�X�V
	void Draw_(Rocket* rocket);																									//�`��
	void invincibleTime_(Player* player, Bird* bird[], Effect* effect,Shield* shield);											//���G���Ԋ֐�
	void changeJumpType(Player* player, Bird* bird[], Effect* effect);															//�W�����v�؂�ւ�
	void ridingRocket_();																										//���P�b�g��Ԓ�

	//�Q�b�^�[
	VECTOR Getposition_()const { return position_; }
	float  Getgravity_()const { return gravity_; }
	bool   GetisFall_()const { return isFall_; }
	double Getstamina_()const { return stamina_; }
	int	   GetmodelHandle_()const { return modelHandle_; }
	bool   GetisSuperJump_()const { return isSuperJump_; }
	float  GetjumpUpSpeed_()const { return jumpUpSpeed_; }
	bool   GetcanStartJump_()const { return canStartJump_; }
	int	   GetconsumingStaminaCount_()const { return consumingStaminaCount_; }
	float  GetmaxNormalJumpCount_()const { return maxNormalJumpCount_; }

private:
	int	   modelHandle_;						//���f���n���h��
	VECTOR position_;							//�|�W�V����
	bool   isPrevSpace_				= false;	//�X�y�[�X���������m�t���O
	int	   jumpCount_				= 0;		//�W�����v�J�E���g
	bool   isJumpCount_				= false;	//�W�����v�J�E���g�t���O
	float  jumpUpSpeed_				= 0.00f;	//�W�����v�㏸��
	float  gravity_					= 0.00f;	//�d��
	bool   isFall_					= false;	//�����Ă��邩�t���O
	float  xAddSpeed_				= 0.00f;	//x���W��+�ړ���
	float  xSubtractSpeed_			= 0.00f;	//x���W��-�ړ���
	bool   isInvincible_			= false;	//���G�t���O
	int    invincibleCount_			= 0;		//���G�J�E���g
	double stamina_					= 0.00;		//�X�^�~�i
	int    staminaCount_			= 0;		//�X�^�~�i�J�E���g
	float  maxJumpCount_			= 70.00f;	//�ő�W�����v�J�E���g
	bool   isSuperJump_				= false;	//�X�[�p�[�W�����v���邩�t���O
	int	   superJumpSound_;						//�X�[�p�[�W�����v�T�E���h
	int    jumpSound_;							//�W�����v�T�E���h
	int	   damageSound_;						//�_���[�W�T�E���h
	bool   isFacingRight			= true;		//�E�����t���O
	bool   canStartJump_			= false;	//�W�����v�J�n�ł��邩�t���O
	float  maxNormalJumpCount_		= 0.00f;	//�ʏ�W�����v�ő�J�E���g
	int	   consumingStaminaCount_	= 0;		//����X�^�~�i�J�E���g
	int	   chargingSound_;						//�`���[�W��
	bool   canStartChargingSound_	= true;		//�`���[�W���J�n�ł��邩

	void   jump_(Animation* animation, Player* player, Effect* effect, Wing* wing);	//�W�����v�֐�
	void   nowJump_();																//�W�����v���֐�
	void   chargeJump_(Effect* effect, ChargeEffect* chargeEffect);					//�W�����v���߂�֐�
	void   moveX_();																//���ړ�
	void   facing_();																//�ǂ�������
	void   pushBack_();																//�����߂�
	void   healStamina_();															//�X�^�~�i��
	void   allHealStamina_(CupCake* cupCake);										//�X�^�~�i�S��
	void   abducted_(UFO* ufo);														//�U�������				
};