#pragma once

class Player;
class BackGraph;
class Bird;
class Camera;
class TitleGraph;
class SelectScene;
class UI;
class Animation;
class Effect;
class Rocket;
class Timer;
class Routine;

enum
{
    TITLE,
    PLAY,
    CLEAR,
    PAUSE,
    TUTORIAL,
    DICTIONARY
};

class ProceedScene
{
public:
	ProceedScene();
	~ProceedScene();

    void proceedPLAY(bool& isPrevButton);
    void proceedCLEAR(Timer* timer);
    void proceedTITLE(bool& isPrevButton, Timer* timer, Player* player, TitleGraph* titleGraph, SelectScene* selectScene, Bird* bird[], bool& canPlayBGM,
        bool& canPlayClearSound, Animation* animation, bool& canPlayGame, Routine* routine);
    void proceedPAUSE(Player* player, Timer* timer, int staminaRedGage, BackGraph* backGraph, Bird* bird[], bool& isPrevButton,
        Camera* camera, UI* ui, Effect* effect, Rocket* rocket, Routine* routine);
    void allInit(Timer* timer, Player* player, TitleGraph* titleGraph, SelectScene* selectScene, Bird* bird[], bool& canPlayBGM, bool& canPlayClearSound
        , Animation* animation, bool& canPlayGame, Routine* routine);
    void sceneProceeder(BackGraph* backGraph, Bird* bird[], Camera* camera, Timer* timer, bool& isPrevButton, Player* player,
        SelectScene* selectScene, int staminaRedGage, TitleGraph* titleGraph, bool& canPlayBGM, bool& canPlayClearSound, UI* ui, Animation* animation,
        bool& canPlayGame, Effect* effect, Rocket* rocket,Routine* routine);
    void proceedDictionary_();
    void tutorialToPlay_();

    int GetaddTimer_()const { return addTimer_; }
    int GetscneType_()const { return sceneType_; }

private:
    int dicideSound_;       //決定サウンド
    int startPauseTimer_;   //ポーズ開始タイマー
    int tmpTimer_;          //一時保存タイマー(ポーズ画面の経過時間を計測する)
    int addTimer_;          //加算用タイマー
    int finishSound_;       //ゲーム終了音
    int sceneType_;         //画面遷移
    bool isPrevButton_;
};