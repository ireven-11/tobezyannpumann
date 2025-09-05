#include"includeAll.h"

Routine::Routine()
{
    titleBGM_           = LoadSoundMem("sound/titlebgm.mp3");
    ChangeVolumeSoundMem(150, titleBGM_);
    clearSound_         = LoadSoundMem("sound/clear.mp3");
    ChangeVolumeSoundMem(200, clearSound_);
    startSound_         = LoadSoundMem("sound/start.mp3");
    ChangeVolumeSoundMem(175, startSound_);
    pauseScreenHandle_  = MakeScreen(screenWIDTH, screenHEIGHT, TRUE);
    canPlayGame_        = false;
    isTutorial1_        = true;
    isTutorial2_        = false;
    isTutorial3_        = false;
    isTutorial4_        = false;
    isTutorial5_        = false;
    tutorialCount1_     = standardNumber;
    tutorialCount2_     = standardNumber;
    tutorialCount3_     = standardNumber;
    tutorialCount4_     = standardNumber;
    tutorialCount5_     = standardNumber;
    hanamaruGraph_      = LoadGraph("img/hanamaru.png");
    correctSound_       = LoadSoundMem("sound/correct.mp3");
    ChangeVolumeSoundMem(200, correctSound_);
}

Routine::~Routine()
{
    DeleteSoundMem(titleBGM_);
    DeleteSoundMem(clearSound_);
    DeleteSoundMem(startSound_);
}

//�A�C�e�����[�`��
void Routine::item_(Rocket* rocket,Timer* timer,bool cannotSpawnTwoItems,Wing* wing,Player* player,Effect* effect,CupCake* cupCake,Shield* shield,SandClock* sandClock,UFO* ufo)
{
    rocket->spawn_(timer, cannotSpawnTwoItems);//10(10%)
    rocket->Update_(timer, cannotSpawnTwoItems, player, effect);
    rocket->Draw_(player);
    wing->spawn_(timer, cannotSpawnTwoItems);//45(40.5%)
    wing->Update_(timer, cannotSpawnTwoItems, player, effect);
    wing->Draw_(player);
    ufo->spawn_(timer, cannotSpawnTwoItems);//
    ufo->Update_(timer, cannotSpawnTwoItems, player, effect);
    ufo->Draw_(player);
    wing->DrawEffectIcon_();
    cupCake->spawn_(timer, cannotSpawnTwoItems);//60(35.7%)
    cupCake->Update_(timer, cannotSpawnTwoItems, player, effect);
    cupCake->Draw_(player);
    sandClock->spawn_(timer, cannotSpawnTwoItems);
    sandClock->Update_(timer, cannotSpawnTwoItems, player, effect);
    sandClock->Draw_(player);
    shield->spawn_(timer, cannotSpawnTwoItems);//100(13.8%)
    shield->Update_(timer, cannotSpawnTwoItems, player, effect);
    shield->Draw_(player);
    shield->DrawEffectIcon_();
}

//�Q�[�����[�v
void Routine::gameRoop_(Camera* camera, Player* player, TitleGraph* titleGraph, UI* ui, SelectScene* selectScene, bool& canPlayBGM,
    ProceedScene* proceedScene, BackGraph* backGraph, Bird* bird[], Timer* timer, bool& isPrevButton, int& staminaRedGage,
    bool& canPlayClearSound, Animation* animation, bool& canPlayGame, Effect* effect, Rocket* rocket, Shield* shield, Wing* wing,
    CupCake* cupCake, bool& cannotSpawnTwoItems, Transition* transition, ClearGraph* clearGraph, SandClock* sandClock, UFO* ufo,
    ChargeEffect* chargeEffect)
{
    while (gameRoopSetting)
    {
        ClearDrawScreen();

        switch (proceedScene->GetscneType_())
        {
        case TITLE:
            camera->Update_(player);

            titleGraph->Update_();

            titleGraph->Draw_();

            ui->drawTitleUI(selectScene);

            if (canPlayBGM)
            {
                PlaySoundMem(titleBGM_, DX_PLAYTYPE_LOOP, TRUE);
                canPlayBGM = false;
            }

            proceedScene->sceneProceeder(backGraph, bird, camera, timer, isPrevButton, player, selectScene, staminaRedGage, titleGraph, canPlayBGM, canPlayClearSound, ui, animation, canPlayGame, effect, rocket,this);

            break;

        case PLAY:
            camera->Update_(player);
            backGraph->Draw_(player);
            player->Draw_(rocket);

            //�n�ʂ̑���
            //DrawGrid(groundSize, divideNum);
            DrawTriangle3D(VGet(-100, 0, -100), VGet(-100, 0, 100), VGet(1000, 0, -100), GetColor(100, 50, 50), TRUE);

            //�Q�[���ł���Ƃ������X�V�Ȃǂ�����i�ꕔ���O�j
            if (canPlayGame)
            {
                //��������
                timer->limit_(proceedScene, sandClock);

                //�v���C���[
                animation->Update(player);
                player->changeJumpType(player, bird, effect);
                player->invincibleTime_(player, bird, effect, shield);
                player->Update_(animation, player, effect, wing, rocket, cupCake,ufo,chargeEffect);
                effect->Draw_();

                //��
                for (int i = 0; i < maxBirdNumber; i++)
                {

                    bird[i]->Update_(i);
                    bird[i]->Draw_(player, i);
                }
                animation->UpdateFlying_(bird);

                //�A�C�e�����[�`��
                item_(rocket, timer, cannotSpawnTwoItems, wing, player, effect, cupCake, shield, sandClock,ufo);

                //ui
                ui->drawPlayUI(timer, player, staminaRedGage,bird);
                ui->finishUI_(timer);

                //��ʑJ��
                proceedScene->sceneProceeder(backGraph, bird, camera, timer, isPrevButton, player, selectScene, staminaRedGage, titleGraph, canPlayBGM, canPlayClearSound, ui, animation, canPlayGame, effect, rocket,this);
            }
            //�Q�[���J�n�O
            else
            {
                ui->drawPlayUI(timer, player, staminaRedGage,bird);

                ui->drawReadyUI();

                transition->Update();

                //�G���^�[�L�[�ŃQ�[���J�n
                if (CheckHitKey(KEY_INPUT_RETURN) == 1 && transition->GettransitionCount_() > maxTransitionCount)
                {
                    if (!isPrevButton)
                    {
                        canPlayGame = true;
                        PlaySoundMem(startSound_, DX_PLAYTYPE_BACK, TRUE);
                        //���Ԍv���J�n
                        timer->start_();
                        transition->Reset();
                    }
                    isPrevButton = true;
                }
                else
                {
                    isPrevButton = false;
                }
            }


            break;

        case PAUSE:
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // ���������[�h
            DrawGraph(0, 0, pauseScreenHandle_, TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �ʏ�`��ɖ߂�

            ui->drawPauseUI(selectScene);

            proceedScene->sceneProceeder(backGraph, bird, camera, timer, isPrevButton, player, selectScene, staminaRedGage, titleGraph, canPlayBGM, canPlayClearSound, ui, animation, canPlayGame, effect, rocket,this);

            break;

        case CLEAR:
            titleGraph->Update_();
            titleGraph->Draw_();

            ui->drawClearUI(selectScene, player);

            clearGraph->Draw_(player, ui);

            if (canPlayClearSound)
            {
                PlaySoundMem(clearSound_, DX_PLAYTYPE_BACK, TRUE);
                canPlayClearSound = false;
            }

            proceedScene->sceneProceeder(backGraph, bird, camera, timer, isPrevButton, player, selectScene, staminaRedGage, titleGraph, canPlayBGM, canPlayClearSound, ui, animation, canPlayGame, effect, rocket,this);

            break;

        case DICTIONARY:
            camera->Update_(player);

            //�w�i
            DrawExtendGraph(standardNumber, standardNumber, screenWIDTH, screenHEIGHT, ui->GetdictionaryGraph_(), TRUE);
            ui->dictionaryUI();

            //�A�C�e����I��
            ui->selectItem_();

            //�A�C�e��������`��
            switch (ui->GetitemNumber_())
            {
            case 0:
                ui->explain3DItemUI_(cupCakeNameText.x, cupCakeNameText.y, "�J�b�v�P�[�L", GetColor(255, 255, 255), ui->GetfontSize125_(), cupCake->GetmodelHandle_(),
                    dictionaryCupCake, itemEffectText.x, itemEffectText.y, "�X�^�~�i��S�񕜂���", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;
                
            case 1:
                ui->explain3DItemUI_(rocketNameText.x, rocketNameText.y, "���P�b�g", GetColor(255, 255, 255), ui->GetfontSize125_(), rocket->GetmodelHandle_(),
                    dictionaryRocket, itemEffectText.x, itemEffectText.y, "���P�b�g�ɏ�Ԃ�\n��莞�ԏ㏸��������", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;

            case 2:
                ui->explain3DItemUI_(sandClockNameText.x, sandClockNameText.y, "�����v", GetColor(255, 255, 255), ui->GetfontSize125_(), sandClock->GetmodelHandle_(),
                    dictionarySandClock, itemEffectText.x, itemEffectText.y, "�������Ԃ�10�b���₷", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;
                
            case 3:
                ui->explain3DItemUI_(shieldNameText.x, shieldNameText.y, "�V�[���h", GetColor(255, 255, 255), ui->GetfontSize125_(), shield->GetmodelHandle_(),
                    dictionaryShield, itemEffectText.x, itemEffectText.y, "��莞�ԃ_���[�W��\n����������", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;

            case 4:
                ui->explain3DItemUI_(ufoNameText.x, ufoNameText.y, "UFO", GetColor(255, 255, 255), ui->GetfontSize125_(), ufo->GetmodelHandle_(),
                    dictionaryUfo, itemEffectText.x, itemEffectText.y, "UFO�ɗU�������\n�����_���ȏꏊ��\n��΂����", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;

            case 5:
                ui->explain3DItemUI_(wingNameText.x, wingNameText.y, "�E�B���O", GetColor(255, 255, 255), ui->GetfontSize125_(), wing->GetmodelHandle_(),
                    dictionaryWing, itemEffectText.x, itemEffectText.y, "�W�����v�͂�����\n2�{�ɂȂ�", GetColor(255, 255, 255), ui->GetfontSize75_());
                break;
            }

            proceedScene->proceedTITLE(isPrevButton, timer, player, titleGraph, selectScene, bird, canPlayBGM, canPlayClearSound, animation, canPlayGame, this);

            break;

        case TUTORIAL:
            camera->Update_(player);
            backGraph->Draw_(player);
            ui->tutorialUI_(player, bird, this);
            player->Draw_(rocket);
            //�v���C���[
            animation->Update(player);
            player->changeJumpType(player, bird, effect);
            player->invincibleTime_(player, bird, effect, shield);
            player->Update_(animation, player, effect, wing, rocket, cupCake, ufo,chargeEffect);
            chargeEffect->Draw_(player);
            effect->Draw_();
           
            if (isTutorial1_ && player->Getposition_().y > floatStandardNumber)
            {
                ++tutorialCount1_;

                //���Ɉړ�
                if (tutorialCount1_ > 100)
                {
                    DrawExtendGraph(700, 200, 1200, 700, hanamaruGraph_, TRUE);
                    PlaySoundMem(correctSound_, DX_PLAYTYPE_NORMAL, TRUE);
                    isTutorial1_    = false;
                    isTutorial2_    = true;
                    tutorialCount1_ = standardNumber;
                    player->Init_();
                }
            }
            else if (isTutorial2_)
            {
                if (player->Getposition_().y > standardNumber && CheckHitKey(KEY_INPUT_SPACE) == TRUE)
                {
                    ++tutorialCount2_;
                }
                if (tutorialCount2_ > 100 && CheckHitKey(KEY_INPUT_SPACE) == FALSE)
                {
                    DrawExtendGraph(700, 200, 1200, 700, hanamaruGraph_, TRUE);
                    PlaySoundMem(correctSound_, DX_PLAYTYPE_NORMAL, TRUE);
                    isTutorial2_ = false;
                    isTutorial3_ = true;
                    tutorialCount2_ = standardNumber;
                    player->Init_();
                }
            }
            else if (isTutorial3_)
            {
                if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE || CheckHitKey(KEY_INPUT_LEFT) == TRUE)
                {
                    ++tutorialCount3_;
                }

                if (tutorialCount3_ > 100)
                {
                    DrawExtendGraph(700, 200, 1200, 700, hanamaruGraph_, TRUE);
                    PlaySoundMem(correctSound_, DX_PLAYTYPE_NORMAL, TRUE);
                    isTutorial3_ = false;
                    isTutorial4_ = true;
                    tutorialCount3_ = standardNumber;
                    player->Init_();
                }
            }
            else if (isTutorial4_)
            {
                //��
                for (int i = 0; i < maxBirdNumber; i++)
                {
                    bird[i]->Update_(i);
                    bird[i]->Draw_(player, i);
                }
                animation->UpdateFlying_(bird);

                bool tmp = superJump(player, bird, effect);

                if (tmp == true)
                {
                    DrawExtendGraph(700, 200, 1200, 700, hanamaruGraph_, TRUE);
                    PlaySoundMem(correctSound_, DX_PLAYTYPE_NORMAL, TRUE);
                    isTutorial4_ = false;
                    isTutorial5_ = true;
                    tutorialCount4_ = standardNumber;
                    player->Init_();
                }
            }
            else if (isTutorial5_)
            {
                timer->limit_(proceedScene, sandClock);
                //�A�C�e�����[�`��
                item_(rocket, timer, cannotSpawnTwoItems, wing, player, effect, cupCake, shield, sandClock, ufo);
            }
            
            //�v���C��ʂ�
            if (CheckHitKey(KEY_INPUT_RETURN) == true)
            {
                proceedScene->allInit(timer,player,titleGraph,selectScene,bird,canPlayBGM,canPlayClearSound
                    ,animation,canPlayGame,this);

                isTutorial1_ = true;
                isTutorial2_ = false;
                isTutorial3_ = false;
                isTutorial4_ = false;
                isTutorial5_ = false;

                proceedScene->tutorialToPlay_();
            }


            break;
        }

        //���t���b�V�����[�g�΍�
        setFPS();

        ScreenFlip();
    }
}

void Routine::resetTutorial_()
{
    isTutorial1_ = true;
    isTutorial2_ = false;
    isTutorial3_ = false;
    isTutorial4_ = false;
    isTutorial5_ = false;
}