#include"DxLib.h"
#include"common.h"
#include"selectScene.h"
#include"proceedScene.h"

//�R���X�g���N�^
SelectScene::SelectScene()
{
    selectSound_ = LoadSoundMem("sound/select.mp3");
    ChangeVolumeSoundMem(255, selectSound_);
}

//�f�X�g���N�^
SelectScene::~SelectScene()
{
    DeleteSoundMem(selectSound_);
}

//������
void SelectScene::Init_()
{
    sceneNumber_ = standardNumber;
}

//�X�V
void SelectScene::Update(int sceneType)
{
    //�|�[�Y�ƃ^�C�g���̎������ő�V�[���i���o�[���ς��
    if (sceneType == PAUSE || sceneType == TITLE)
    {
        maxSceneNumber_ = maxPauseSceneNumber;
    }
    else
    {
        maxSceneNumber_ = maxOtherSceneNumber;
    }

    //�㉺���L�[�őI��
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