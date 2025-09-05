#include"DxLib.h"
#include"backGraph.h"
#include"common.h"
#include"player.h"

//コンストラクタ
BackGraph::BackGraph()
{
	x1_				= standardNumber;
	x2_				= screenWIDTH;
	y1_				= standardNumber;
	y2_				= screenHEIGHT;
    graph1_			= LoadGraph("img/sky/back-s04a.png");
	graph2_			= LoadGraph("img/sky/back-s04b.png");
	graph3_			= LoadGraph("img/sky/back-s04c.png");
	graph4_			= LoadGraph("img/sky/back-s04d.png");
	graph5_			= LoadGraph("img/sky/back-s04e.png");
}

//デストラクタ
BackGraph::~BackGraph()
{
	DeleteGraph(graph1_);
	DeleteGraph(graph2_);
	DeleteGraph(graph3_);
	DeleteGraph(graph4_);
	DeleteGraph(graph5_);
}

//描画
void BackGraph::Draw_(Player* player)
{
	//プレイヤーの高さによって背景を変える
	if (player->Getposition_().y < changeGraphPosition)
	{
		graph_ = graph1_;
	}
	else if (player->Getposition_().y < changeGraphPosition * 2)
	{
		graph_ = graph2_;
	}
	else if (player->Getposition_().y < changeGraphPosition * 3)
	{
		graph_ = graph3_;
	}
	else if (player->Getposition_().y < changeGraphPosition * 4)
	{
		graph_ = graph4_;
	}
	else
	{
		graph_ = graph5_;
	}

	for (int i = standardNumber; i < maxGraphNumber; i++)
	{
		DrawExtendGraph(x1_, y1_ + player->Getposition_().y - screenHEIGHT * i, x2_, y2_ + player->Getposition_().y - screenHEIGHT * i, graph_, TRUE);
	}
}