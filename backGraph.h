#pragma once

const float changeGraphPosition = 1000.00f;	//�摜�؂�ւ����l
const int   maxGraphNumber		= 6;		//�摜�����{�P�ifor���[�v)

class Player;

class BackGraph
{
public:
	BackGraph();				//�R���X�g���N�^
	~BackGraph();				//�f�X�g���N�^

	void Draw_(Player* player);	//�`��

private:
	int x1_{};			//x1���W
	int x2_{};			//x2���W
	int y1_{};			//y1���W
	int y2_{};			//y2���W
	int graph_;			//�摜�n���h��
	int graph1_;		//�摜�P
	int graph2_;		//�摜�Q
	int graph3_;		//�摜�R
	int graph4_;		//�摜�S
	int graph5_;		//�摜�T
};