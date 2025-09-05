#include"DxLib.h"
#include"common.h"
#include"selectScene.h"
#include"proceedScene.h"

//コンストラクタ
SelectScene::SelectScene()
{
    selectSound_ = LoadSoundMem("sound/select.mp3");
    ChangeVolumeSoundMem(255, selectSound_);
}

//デストラクタ
SelectScene::~SelectScene()
{
    DeleteSoundMem(selectSound_);
}

//初期化
void SelectScene::Init_()
{
    sceneNumber_ = standardNumber;
}

//更新
void SelectScene::Update(int sceneType)
{
    //ポーズとタイトルの時だけ最大シーンナンバーが変わる
    if (sceneType == PAUSE || sceneType == TITLE)
    {
        maxSceneNumber_ = maxPauseSceneNumber;
    }
    else
    {
        maxSceneNumber_ = maxOtherSceneNumber;
    }

    //上下矢印キーで選択
    if (sceneType != PLAY)
    {
        if (CheckHitKey(KEY_INPUT_UP) == 1)
        {
            if (!isPrevButton_)
            {
                --sceneNumber_;

                PlaySoundMem(selectSound_, DX_PLAYTYPE_BACK, TRUE);

                if (sceneNumber_ < standardNumber)
                {
                    sceneNumber_ = standardNumber;
                }
            }
            isPrevButton_ = true;
        }
        else if (CheckHitKey(KEY_INPUT_DOWN) == 1)
        {
            if (!isPrevButton_)
            {
                ++sceneNumber_;

                PlaySoundMem(selectSound_, DX_PLAYTYPE_BACK, TRUE);

                if (sceneNumber_ > maxSceneNumber_)
                {
                    sceneNumber_ = maxSceneNumber_;
                }
            }
            isPrevButton_ = true;
        }
        else
        {
            isPrevButton_ = false;
        }
    }
}