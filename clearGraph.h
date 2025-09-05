#pragma once
#include"common.h"

const int MTfuziHEIGHT			= 3776;	//�x�m�R�̍���
const int MTibukiHEIGHT			= 1377;	//�ɐ��R�̍���
const int tokyoskytreeHEIGHT	= 634;	//�X�J�C�c���[�̍���
const int matyupityuHEIGHT		= 2430;	//�}�`���s�`���̍���
const int monnburannHEIGHT		= 4810;	//�����u�����̍���
const int wideWIDTH				= 1000;	//�����摜�̕�
const int tallWIDTH				= 450;	//�c���摜�̕�
const int wideHEIGHT			= 550;	//�����摜�̍���
const int tallHEIGHT			= 600;	//�c���摜�̍���
const int wideX					= 100;	//�����摜�̏�����
const int wideY					= 300;	//�����摜�̏�����
const int tallX					= 375;	//�c���摜�̏�����
const int tallY					= 275;	//�c���摜�̏�����
const int rankPositionX			= 1225;	//�����N�����W
const int rankPositionY			= 250;	//�����N�����W
const int lineX					= 1150;	//��X
const int lineY					= 363;	//��Y
const int lineRange				= 1825;	//���͈�
const int textPositionX			= 1190;	//�e�L�X�g�����W
const int textPositionY			= 400;	//�e�L�X�g�����W
const int kilimanjaroHEIGHT		= 5895;	//�L���}���W�����̍���
const int everestHEIGHT			= 8848;	//�G�x���X�g����

class Player;
class UI;

class ClearGraph
{
public:
	ClearGraph();	//�R���X�g���N�^
	~ClearGraph();	//�f�X�g���N�^

	void Draw_(Player* player,UI* ui);	//�`��

private:
	int MTfuziGraph_;		//�x�m�R
	int MTibukiGraph_;		//�ɐ��R
	int tokyoskytreeGraph_;	//�X�J�C�c���[
	int groundOfMother_;	//��Ȃ��n
	int matyupityu_;		//�}�`���s�`��
	int MTmonnburann_;		//�����u����(�R)
	int monnburannCake_;	//�����u����(�P�[�L)
	int ferrisWheel_;		//�ϗ���
	int kilimanjaroGraph_;	//�L���}���W�����摜
	int everestGraph_;		//�G�x���X�g
};