#include"DxLib.h"
#include"proceedScene.h"
#include"common.h"
#include"player.h"
#include"UI.h"
#include"bird.h"
#include"backGraph.h"
#include"camera.h"
#include"titleGraph.h"
#include"selectScene.h"
#include"animation.h"
#include"effect.h"
#include"item.h"
#include"timer.h"
#include"routine.h"

//コンストラクタ
ProceedScene::ProceedScene()
{
    dicideSound_        = LoadSoundMem("sound/dicide.mp3");
    ChangeVolumeSoundMem(200, dicideSound_);
    tmpTimer_           = standardNumber;
    addTimer_           = standardNumber;
    finishSound_        = LoadSoundMem("sound/finish.mp3");
    ChangeVolumeSoundMem(200, finishSound_);
    sceneType_          = TITLE;
    isPrevButton_       = false;
}

//デストラクタ
ProceedScene::~ProceedScene()
{
    DeleteSoundMem(dicideSound_);
    DeleteSoundMem(finishSound_);
}

//プレイ画面へ
void ProceedScene::proceedPLAY(bool& isPrevButton)
{
    if (CheckHitKey(KEY_INPUT_RETURN) == 1)
    {
        if (!isPrevButton_)
        {
            //ポーズからプレイに戻るときだけ
            if (sceneType_ == PAUSE)
            {
                addTimer_ += tmpTimer_ / 1000;
            }

            sceneType_ = PLAY;
            PlaySoundMem(dicideSound_, DX_PLAYTYPE_BACK, TRUE);
        }
        isPrevButton_ = true;
    }
    else
    {
        isPrevButton_ = false;
    }

    //デバッグ用チュートリアル
    if (CheckHitKey(KEY_INPUT_T) == true)
    {
        sceneType_ = TUTORIAL;
    }
}

//クリア画面へ
void ProceedScene::proceedCLEAR(Timer* timer)
{
    if (timer->GetsecondsTimer_() == standardNumber || CheckHitKey(KEY_INPUT_1) == 1)
    {
        sceneType_ = CLEAR;

        //ゲーム終了音をながす
        PlaySoundMem(finishSound_, DX_PLAYTYPE_NORMAL, TRUE);
    }
}

//タイトルへ
void ProceedScene::proceedTITLE(bool& isPrevButton, Timer* timer,Player* player,TitleGraph* titleGraph, SelectScene* selectScene,Bird* bird[], bool& canPlayBGM, bool& canPlayClearSound, Animation* animation, bool& canPlayGame,Routine* routine)
{
    //タイトルへ戻るときについでに初期化する
    if (CheckHitKey(KEY_INPUT_RETURN) == 1)
    {
        if (!isPrevButton_)
        {
            if (sceneType_==DICTIONARY)
            {
                PlayMovie("video/flipright1.mp4", 1, DX_PLAYTYPE_NORMAL);
            }
            sceneType_ = TITLE;
            PlaySoundMem(dicideSound_, DX_PLAYTYPE_BACK, TRUE);
            allInit(timer, player, titleGraph, selectScene,bird,canPlayBGM,canPlayClearSound,animation, canPlayGame, routine);
        }
        isPrevButton_ = true;
    }
    else
    {
        isPrevButton_ = false;
    }
}

//ポーズ画面へ(バグあり)
void ProceedScene::proceedPAUSE(Player* player,Timer* timer,int staminaRedGage,BackGraph* backGraph,Bird* bird[], bool& isPrevButton,Camera* camera,UI* ui,Effect* effect,Rocket* rocket,Routine* routine)
{
    if (CheckHitKey(KEY_INPUT_RCONTROL) == 1 || CheckHitKey(KEY_INPUT_LCONTROL) == 1)
    {
        if (!isPrevButton)
        {
            //ポーズ開始時間を計測する
            startPauseTimer_    = GetNowCount();
            tmpTimer_           = standardNumber;

            //画像ハンドルに描画し直す
            SetDrawScreen(routine->GetpauseScreenHandle_());
            ClearDrawScreen();

            camera->Update_(player);
            backGraph->Draw_(player);
            //地面の代わり
            //DrawGrid(groundSize, divideNum);
            DrawTriangle3D(VGet(-100, 0, -100), VGet(-100, 0, 100), VGet(1000, 0, -100), GetColor(100, 50, 50), TRUE);
            ui->drawPlayUI(timer, player, staminaRedGage,bird);
            player->Draw_(rocket);
            for (int i = 0; i < maxBirdNumber; i++)
            {
                bird[i]->Draw_(player,i);
            }
            //バグ：ポーズ中にエフェクトが発生しない
            effect->Draw_();

            //バッグにするとポーズの後にフィニッシュUiが描画されなくなる
            SetDrawScreen(DX_SCREEN_FRONT);

            sceneType_ = PAUSE;

            PlaySoundMem(dicideSound_, DX_PLAYTYPE_BACK, TRUE);
        }
        isPrevButton = true;
    }
    else
    {
        isPrevButton = false;
    }
}

//全初期化
void ProceedScene::allInit(Timer* timer, Player* player, TitleGraph* titleGraph,SelectScene* selectScene,Bird* bird[],bool& canPlayBGM ,bool& canPlayClearSound,Animation* animation,bool& canPlayGame,Routine* routine)
{
    timer->reset_();
    player->Init_();
    titleGraph->InitFlag_();
    selectScene->Init_();
    for (int i = 0; i < maxBirdNumber; i++)
    {
        bird[i]->Init_(i);
    }
    canPlayClearSound   = true;
    animation->Init_(player);
    canPlayGame         = false;
    tmpTimer_           = standardNumber;
    addTimer_           = standardNumber;
}

//画面遷移
void ProceedScene::sceneProceeder(BackGraph* backGraph, Bird* bird[], Camera* camera, Timer* timer, bool& isPrevButton, Player* player, SelectScene* selectScene, int staminaRedGage, TitleGraph* titleGraph, bool& canPlayBGM, bool& canPlayClearSound,UI* ui,Animation* animation, bool& canPlayGame,Effect* effect,Rocket* rocket,Routine* routine)
{
    selectScene->Update(sceneType_);

    switch (sceneType_)
    {
    case TITLE:
        if (selectScene->GetsceneNumber_() == 0)
        {
            proceedPLAY(isPrevButton);
        }
        else if (selectScene->GetsceneNumber_() == 1)
        {
            proceedDictionary_();
        }
        else
        {
            if (CheckHitKey(KEY_INPUT_RETURN) == TRUE)
            {
                sceneType_ = TUTORIAL;
                WaitTimer(500);
            }
        }

        break;

    case PLAY:
        proceedCLEAR(timer);
        proceedPAUSE(player, timer, staminaRedGage, backGraph, bird, isPrevButton, camera,ui,effect,rocket,routine);

        break;

    case CLEAR:
        if (selectScene->GetsceneNumber_() == 0)
        {
            proceedPLAY(isPrevButton);//リトライ

            if (sceneType_ == PLAY)
            {
                allInit(timer, player, titleGraph, selectScene,bird, canPlayBGM, canPlayClearSound,animation, canPlayGame, routine);
            }
        }
        else
        {
            proceedTITLE(isPrevButton, timer, player, titleGraph, selectScene,bird, canPlayBGM, canPlayClearSound, animation, canPlayGame, routine);
        }

        break;

    case PAUSE:
        //ポーズ時間を計測
        tmpTimer_ = GetNowCount() - startPauseTimer_;

        if (selectScene->GetsceneNumber_() == 0)
        {
            proceedPLAY(isPrevButton);//元に戻す
        }
        else if(selectScene->GetsceneNumber_() == 1)
        {
            proceedPLAY(isPrevButton);//リトライ

            if (sceneType_ == PLAY)
            {
                allInit(timer, player, titleGraph, selectScene,bird, canPlayBGM, canPlayClearSound,animation, canPlayGame, routine);
            }
        }
        else
        {
            proceedTITLE(isPrevButton, timer, player, titleGraph, selectScene,bird, canPlayBGM, canPlayClearSound, animation, canPlayGame, routine);
        }

        break;
    }
}

void ProceedScene::proceedDictionary_()
{
    if (CheckHitKey(KEY_INPUT_RETURN) == true)
    {
        if (!isPrevButton_)
        {
            PlaySoundMem(dicideSound_, DX_PLAYTYPE_BACK, TRUE);
            PlayMovie("video/flipleft1.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
            sceneType_ = DICTIONARY;
        }
        isPrevButton_ = true;
    }
    else
    {
        isPrevButton_ = false;
    }
}

//チュートリアルからプレイ画面へ
void ProceedScene::tutorialToPlay_()
{
    sceneType_ = PLAY;
}