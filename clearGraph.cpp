#include"DxLib.h"
#include"player.h"
#include"clearGraph.h"
#include"UI.h"
#include"common.h"

//�R���X�g���N�^
ClearGraph::ClearGraph()
{
	//�摜�ǂݍ���
	MTfuziGraph_		= LoadGraph("img/fuzisann.jpg");
	MTibukiGraph_		= LoadGraph("img/ibukiyama.jpg");
	tokyoskytreeGraph_	= LoadGraph("img/sukaituri.jpg");
	groundOfMother_		= LoadGraph("img/gia.jpg");
	matyupityu_			= LoadGraph("img/matyupityu.jpg");
	MTmonnburann_		= LoadGraph("img/monnburann.jpg");
	monnburannCake_		= LoadGraph("img/monnburanncake.jpg");
	ferrisWheel_		= LoadGraph("img/kannrannsya.jpg");
	kilimanjaroGraph_	= LoadGraph("img/Kilimanjaro.jpg");
	everestGraph_		= LoadGraph("img/everest.jpg");
}

//�f�X�g���N�^
ClearGraph::~ClearGraph()
{
	DeleteGraph(MTfuziGraph_);
	DeleteGraph(MTibukiGraph_);
	DeleteGraph(tokyoskytreeGraph_);
	DeleteGraph(groundOfMother_);
	DeleteGraph(matyupityu_);
	DeleteGraph(MTmonnburann_);
	DeleteGraph(monnburannCake_);
	DeleteGraph(ferrisWheel_);
	DeleteGraph(kilimanjaroGraph_);
}

//�`��
void ClearGraph::Draw_(Player* player, UI* ui)
{
	if (player->Getposition_().y * 2 > everestHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, everestGraph_, FALSE);
		DrawStringToHandle(rankPositionX, rankPositionY, "�G�x���X�g��", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�����Ɏ��܂�Ȃ��W�����v��8848\n���[�g�����̃G�x���X�g�𒴂����B\n���͐����ɔF�߂��Ă���W����\n���񂩕ς���Ă���B\n���߂�8848�A����8850�A������\n2020�N��8848.86�ƂȂ��Ă���", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > kilimanjaroHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, kilimanjaroGraph_, FALSE);
		DrawStringToHandle(rankPositionX, rankPositionY, "�L���}���W������", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�������̃W�����v��5895���[�g��\n���̃L���}���W�����𒴂����B\n���O�̈Ӗ��̓X���q�����\n�L���}���u�R�v�A���W������\n�u�����v�őS�̂Ƃ��āu�����P���R�v", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > monnburannHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTmonnburann_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "�����u������", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�َ����̃W�����v��4810���[�g��\n���̃����u�����𒴂����B\n���Ȃ݂ɃP�[�L�̃����u������\n���{���˂炵���B", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > MTfuziHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTfuziGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  �x�m�R��", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�Ƃ�ł��Ȃ��W�����v��3776\n���[�g�����̕x�m�R�𒴂����B\n���ɓ��{�̒���܂ł��Ă��܂���\n�ǂ��܂Œ���ł����̂��낤��", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > matyupityuHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, matyupityu_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "�}�`���s�`����", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�������W�����v��2430���[�g��\n���̃}�`���s�`���𒴂����B\n�}�`���s�`���ƌ����΃C���J�鍑\n������s�̓}�`���s�`����\n��1000���[�g����ɂ������炵��", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > MTibukiHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTibukiGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  �ɐ��R��", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "���Ȃ�̃W�����v��1377���[�g��\n���̈ɐ��R�𒴂����B\n�Ȃ�ƍ�҂Ɩ��O���قړ����B\n����Ɗ򕌂̌����ɂ���R", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > tokyoskytreeHEIGHT)
	{
		DrawExtendGraph(tallX, tallY, tallX + tallWIDTH, tallY + tallHEIGHT, tokyoskytreeGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "�X�J�C�c���[��", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�K���̃W�����v��634���[�g��\n���̓����X�J�C�c���[�𒴂����B\n���Ȃ݂ɃX�J�C�c���[�͌��X610\n���[�g���ɂȂ�\�肾�����炵��", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > floatStandardNumber)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, ferrisWheel_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  �ϗ��ԋ�", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "����̃W�����v�Ŋϗ��Ԃ𒴂����B\n���Ȃ݂ɓ��{�ŏ��̊ϗ��Ԃ�\n4���[�g���̐l�͊ϗ��Ԃ炵���B\n���E�ő�̊ϗ��Ԃ̓h�o�C��\n�u�A�C���h�o�C�v�ō�����\n���ق�250���[�g��", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if(player->Getposition_().y * 2 == floatStandardNumber)
	{
		DrawExtendGraph(tallX, tallY, tallX + tallWIDTH, tallY + tallHEIGHT, groundOfMother_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, " ��Ȃ��n��",GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "�܂����̒n�ʂŏI��...\n�X�^�~�i�ɋC��t���ăW�����v\n���Ă݂悤", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
}