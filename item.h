#pragma once

const int   minimumIconPositionX_	= 250;		//�A�C�R���ŏ����W��
const int   maxIconPositionX_		= 350;		//�A�C�R���ő���WX
const int   minimumIconPositionY_	= 225;		//�A�C�R���ŏ����W��
const int   maxIconPositionY_		= 325;		//�A�C�R���ő���Wy
const VECTOR chanceGraphPosition	= VGet(800, 50, 0);	//�`�����X�摜���W

class Player;
class Effect;
class Timer;

//����
//�A�C�e���o���m���L���Ȃ�𒲂ׂĎQ�l�ɂ���

//�e�N���X
class Item
{
public:
	Item();
	~Item();

	void Update_(Timer* timer, bool& cannotSpawnTwoItems, Player* player, Effect* effect);	//�X�V
	void Draw_(Player* player);																//�`��
	void spawn_(Timer* timer, bool& cannotSpawnTwoItems);									//�X�|�[��
	virtual void DrawEffectIcon_();															//���ʃA�C�R���`��
	virtual void decreseEffectCount_();														//�A�C�e���J�E���g����

	VECTOR Getposition_()const { return position_; }

protected:
	int    modelHandle_{};		//���f���n���h��
	VECTOR position_;			//���W
	int    randomSpawn_;		//�o���m��
	bool   canExsist_;			//���݂ł��邩�t���O
	int    spawnpercentage_;	//�X�|�[���m��
	bool   canRollRandom_;		//�m�����񂹂邩�t���O
	float  speedX_;				//���x�i���j
	float  speedY_;				//���x�i���j
	float  hitBoxX_;			//�����蔻��̑傫��x
	float  hitBoxY_;			//�����蔻��̑傫��y
	int	   effectCount_;		//�A�C�e�����ʃJ�E���g
	int    maxEffectCount_;		//�A�C�e�����ʍő�J�E���g
	VECTOR spawnPosition_;		//�X�|�[�����W
	int	   icon_;				//�A�C�R��
	bool   isMovingRight_;		//�E�����t���O
	bool   isMovingLeft_;		//�������t���O
	bool   onDictionary_;		//�}�ӂɍڂ邩

	const float itemScale_  = 0.050f;	//�A�C�e���̑傫��
	const int   percentage_ = 100;		//%
	const float spawnRange	= 15;		//�X�|�[���Ԋu
	const int   deleteTime	= 10;		//���Ŏ���

	virtual void itemEffect_();	//�A�C�e���̌���
private:
	void move_(Player* player);									//�ړ�
	bool takeItemJudge_(Player* player, Effect* effect);		//�A�C�e���Q�b�g�����蔻��
	void resetPosition_(Player* player);						//�|�W�V�������Z�b�g
	void deathpawn_(Timer* timer, bool& cannotSpawnTwoItems);	//�f�X�|�[��

	int		getItemSound_;	//�A�C�e�����艹
	int		chanceGraph_;	//�`�����X�O���t
	int		blinkcount_;	//�_�ŃJ�E���g

	const float turnMovingPosition_ = 90.0f;	//�������A����W
};