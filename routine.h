#pragma once

class Timer;
class Camera;
class Player;
class TitleGraph;
class UI;
class SelectScene;
class ProceedScene;
class BackGraph;
class Bird;
class Animation;
class Effect;
class Rocket;
class Wing;
class Shield;
class CupCake;
class SandClock;
class Transition;
class ClearGraph;
class UFO;
class ChargeEffect;

class Routine
{
public:
	Routine();
	~Routine();

	void gameRoop_(Camera* camera, Player* player, TitleGraph* titleGraph, UI* ui, SelectScene* selectScene, bool& canPlayBGM,
		ProceedScene* proceedScene, BackGraph* backGraph, Bird* bird[], Timer* timer, bool& isPrevButton, int& staminaRedGage, 
		bool& canPlayClearSound, Animation* animation, bool& canPlayGame, Effect* effect, Rocket* rocket, Shield* shield, Wing* wing, 
		CupCake* cupCake, bool& cannotSpawnTwoItems, Transition* transition, ClearGraph* clearGraph, SandClock* sandClock, UFO* ufo,
		ChargeEffect* chargeEffect);

	int GetpauseScreenHandle_()const { return pauseScreenHandle_; }
	int GetisTutorial1_()const { return isTutorial1_; }
	int GetisTutorial2_()const { return isTutorial2_; }
	int GetisTutorial3_()const { return isTutorial3_; }
	int GetisTutorial4_()const { return isTutorial4_; }
	int GetisTutorial5_()const { return isTutorial5_; }

private:
	void item_(Rocket* rocket, Timer* timer, bool cannotSpawnTwoItems, Wing* wing, Player* player, Effect* effect, CupCake* cupCake, Shield* shield, SandClock* sandClock, UFO* ufo);
	void resetTutorial_();
	
	int		titleBGM_;			//タイトルｂｇｍ
	bool	canPlayGame_;		//ゲームできるかフラグ
	int		clearSound_;		//クリア音
	int		startSound_;		//開始音
	int		pauseScreenHandle_; //スクリーンバッファ(ポーズ画面)
	bool	isTutorial1_;		
	bool	isTutorial2_;
	bool	isTutorial3_;
	bool	isTutorial4_;
	bool	isTutorial5_;
	float	groundSize = 1000.00f;
	int		divideNum = 4;
	int		tutorialCount1_;	//チュートリアルカウント
	int		tutorialCount2_;
	int		tutorialCount3_;
	int		tutorialCount4_;
	int		tutorialCount5_;
	int		hanamaruGraph_;		//はなまる
	int		correctSound_;		//正解音
};