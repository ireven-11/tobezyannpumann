#include"DxLib.h"
#include"player.h"
#include"clearGraph.h"
#include"UI.h"
#include"common.h"

//コンストラクタ
ClearGraph::ClearGraph()
{
	//画像読み込み
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

//デストラクタ
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

//描画
void ClearGraph::Draw_(Player* player, UI* ui)
{
	if (player->Getposition_().y * 2 > everestHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, everestGraph_, FALSE);
		DrawStringToHandle(rankPositionX, rankPositionY, "エベレスト級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "次元に収まらないジャンプで8848\nメートルものエベレストを超えた。\n実は正式に認められている標高が\n何回か変わっている。\n初めは8848、次に8850、そして\n2020年に8848.86となっている", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > kilimanjaroHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, kilimanjaroGraph_, FALSE);
		DrawStringToHandle(rankPositionX, rankPositionY, "キリマンジャロ級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "超次元のジャンプで5895メートル\nものキリマンジャロを超えた。\n名前の意味はスワヒリ語で\nキリマが「山」、ンジャロが\n「白さ」で全体として「白く輝く山」", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > monnburannHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTmonnburann_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "モンブラン級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "異次元のジャンプで4810メートル\nものモンブランを超えた。\nちなみにケーキのモンブランは\n日本発祥らしい。", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > MTfuziHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTfuziGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  富士山級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "とんでもないジャンプで3776\nメートルもの富士山を超えた。\nついに日本の頂上まできてしまった\nどこまで跳んでいくのだろうか", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > matyupityuHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, matyupityu_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "マチュピチュ級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "すごいジャンプで2430メートル\nものマチュピチュを超えた。\nマチュピチュと言えばインカ帝国\nだが首都はマチュピチュの\n約1000メートル上にあったらしい", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > MTibukiHEIGHT)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, MTibukiGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  伊吹山級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "かなりのジャンプで1377メートル\nもの伊吹山を超えた。\nなんと作者と名前がほぼ同じ。\n滋賀と岐阜の県境にある山", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > tokyoskytreeHEIGHT)
	{
		DrawExtendGraph(tallX, tallY, tallX + tallWIDTH, tallY + tallHEIGHT, tokyoskytreeGraph_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "スカイツリー級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "必死のジャンプで634メートル\nもの東京スカイツリーを超えた。\nちなみにスカイツリーは元々610\nメートルになる予定だったらしい", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if (player->Getposition_().y * 2 > floatStandardNumber)
	{
		DrawExtendGraph(wideX, wideY, wideX + wideWIDTH, wideY + wideHEIGHT, ferrisWheel_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, "  観覧車級", GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "数回のジャンプで観覧車を超えた。\nちなみに日本最小の観覧車は\n4メートルの人力観覧車らしい。\n世界最大の観覧車はドバイの\n「アインドバイ」で高さは\n驚異の250メートル", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
	else if(player->Getposition_().y * 2 == floatStandardNumber)
	{
		DrawExtendGraph(tallX, tallY, tallX + tallWIDTH, tallY + tallHEIGHT, groundOfMother_, TRUE);
		DrawStringToHandle(rankPositionX, rankPositionY, " 母なる大地級",GetColor(255, 255, 255), ui->GetfontSize75_());
		DrawLine(lineX, lineY, lineRange, lineY, GetColor(0, 0, 0));
		DrawStringToHandle(textPositionX, textPositionY, "まさかの地面で終了...\nスタミナに気を付けてジャンプ\nしてみよう", GetColor(255, 255, 255), ui->GetfontSize40_());
	}
}