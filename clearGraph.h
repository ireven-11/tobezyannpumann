#pragma once
#include"common.h"

const int MTfuziHEIGHT			= 3776;	//富士山の高さ
const int MTibukiHEIGHT			= 1377;	//伊吹山の高さ
const int tokyoskytreeHEIGHT	= 634;	//スカイツリーの高さ
const int matyupityuHEIGHT		= 2430;	//マチュピチュの高さ
const int monnburannHEIGHT		= 4810;	//モンブランの高さ
const int wideWIDTH				= 1000;	//横長画像の幅
const int tallWIDTH				= 450;	//縦長画像の幅
const int wideHEIGHT			= 550;	//横長画像の高さ
const int tallHEIGHT			= 600;	//縦長画像の高さ
const int wideX					= 100;	//横長画像の初期ｘ
const int wideY					= 300;	//横長画像の初期ｙ
const int tallX					= 375;	//縦長画像の初期ｘ
const int tallY					= 275;	//縦長画像の初期ｙ
const int rankPositionX			= 1225;	//ランクｘ座標
const int rankPositionY			= 250;	//ランクｙ座標
const int lineX					= 1150;	//線X
const int lineY					= 363;	//線Y
const int lineRange				= 1825;	//線範囲
const int textPositionX			= 1190;	//テキストｘ座標
const int textPositionY			= 400;	//テキストｙ座標
const int kilimanjaroHEIGHT		= 5895;	//キリマンジャロの高さ
const int everestHEIGHT			= 8848;	//エベレスト高さ

class Player;
class UI;

class ClearGraph
{
public:
	ClearGraph();	//コンストラクタ
	~ClearGraph();	//デストラクタ

	void Draw_(Player* player,UI* ui);	//描画

private:
	int MTfuziGraph_;		//富士山
	int MTibukiGraph_;		//伊吹山
	int tokyoskytreeGraph_;	//スカイツリー
	int groundOfMother_;	//母なる大地
	int matyupityu_;		//マチュピチュ
	int MTmonnburann_;		//モンブラン(山)
	int monnburannCake_;	//モンブラン(ケーキ)
	int ferrisWheel_;		//観覧車
	int kilimanjaroGraph_;	//キリマンジャロ画像
	int everestGraph_;		//エベレスト
};