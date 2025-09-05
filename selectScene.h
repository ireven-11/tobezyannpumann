#pragma once

const int maxPauseSceneNumber = 2;//ポーズ画面の最大シーンナンバー
const int maxOtherSceneNumber = 1;//他画面の最大シーンナンバー

class SelectScene
{
public:
	SelectScene();	//コンストラクタ
	~SelectScene();	//デストラクタ

	void Update(int sceneType);	//更新
	void Init_();				//初期化

	int GetsceneNumber_()const { return sceneNumber_; }

private:
	int		sceneNumber_	= 0;	//シーンナンバー
	int		maxSceneNumber_	= 2;	//最大シーンナンバー
	bool	isPrevButton_	= false;//ボタン長押し防ぐフラグ
	int		selectSound_;			//セレクトサウンド
};