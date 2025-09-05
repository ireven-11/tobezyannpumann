#pragma once

const float changeGraphPosition = 1000.00f;	//画像切り替え数値
const int   maxGraphNumber		= 6;		//画像枚数＋１（forループ)

class Player;

class BackGraph
{
public:
	BackGraph();				//コンストラクタ
	~BackGraph();				//デストラクタ

	void Draw_(Player* player);	//描画

private:
	int x1_{};			//x1座標
	int x2_{};			//x2座標
	int y1_{};			//y1座標
	int y2_{};			//y2座標
	int graph_;			//画像ハンドル
	int graph1_;		//画像１
	int graph2_;		//画像２
	int graph3_;		//画像３
	int graph4_;		//画像４
	int graph5_;		//画像５
};