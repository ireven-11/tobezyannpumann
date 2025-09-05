#include"DxLib.h"
#include"setting.h"
#include"common.h"
#include"EffekseerForDXLib.h"

//画面設定
int setScreen()
{
    ChangeWindowMode(TRUE);				        //ウィンドウモードにする
    SetWindowStyleMode(7);				        //最大化ボタンが存在するウインドウモードに変更
    SetWindowSizeChangeEnableFlag(TRUE, FALSE); //サイズ変更を可能にする
    SetWindowSize(screenWIDTH, screenHEIGHT);   //ウインドウサイズはゲーム画面と一致させる
    SetMainWindowText("飛べ！ジャンプマン！");	//名前をセット
    SetDrawScreen(DX_SCREEN_FRONT);		        //背景をセットする
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//ウィンドウのサイズとカラーモードを決める

	//ライブラリ初期化でエラー起きたら終了
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	return 0;
}

//エフェクシア設定
int setEffekseer()
{
	// DirectX9を使用するようにする。(DirectX11も可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	// Effekseerを初期化する。
	// 引数には画面に表示する最大パーティクル数を設定する。
	if (Effkseer_Init(8000) == -1)
	{
		/*return -1;*/
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Effekseerに2D描画の設定をする。(画面の幅と高さを引数として持たせる)
	//Effekseer_Set2DSetting(screenWIDTH, screenHEIGHT);

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	return 0;
}

//fps設定
void setFPS()
{
	//ここの部分の数値を増やすほどｆｐｓがさがっていく
	const int fps = 32;

	int term;
	static int t = standardNumber;
	term = GetNowCount() - t;
	if (fps - term > standardNumber)
		Sleep(fps - term);
	t = GetNowCount();
}