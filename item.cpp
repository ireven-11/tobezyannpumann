#include"DxLib.h"
#include"item.h"
#include"common.h"
#include"player.h"
#include"effect.h"
#include"timer.h"

//�R���X�g���N�^
Item::Item()
{
    randomSpawn_        = standardNumber;
    position_           = VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
    canExsist_          = false;
    spawnpercentage_    = standardNumber;
    canRollRandom_      = true;
    speedX_             = floatStandardNumber;
    speedY_             = floatStandardNumber;
    hitBoxX_            = floatStandardNumber;
    hitBoxY_            = floatStandardNumber;
    effectCount_        = standardNumber;
    maxEffectCount_     = standardNumber;
    spawnPosition_      = VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber);
    getItemSound_       = LoadSoundMem("sound/getItem.mp3");
    isMovingRight_      = true;
    isMovingLeft_       = false;
    onDictionary_       = false;
    ChangeVolumeSoundMem(240, getItemSound_);
    chanceGraph_        = LoadGraph("img/chance2.png");
    blinkcount_         = standardNumber;
}

//�f�X�g���N�^
Item::~Item()
{
    MV1DeleteModel(modelHandle_);
    DeleteGraph(icon_);
    DeleteSoundMem(getItemSound_);
}

//�X�V
void Item::Update_(Timer* timer, bool& cannotSpawnTwoItems,Player* player,Effect* effect)
{
    //�A�C�e���̑傫�����Z�b�g
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
    MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber));

    if (canExsist_)
    {
        //�ړ�
        move_(player);

        // �RD���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle_, position_);

        //�v���C���[�Ƃ̓����蔻��
        canExsist_ = takeItemJudge_(player,effect);

        //�L���L��
        effect->kirakiraCounter_();
        effect->kirakira_(this);

        //�A�C�e���̌��ʂ𔭓�
        if (!canExsist_)
        {
            itemEffect_();
        }
    }
    else
    {
        //�A�C�e�����o���ʒu�ɖ߂�
        resetPosition_(player);
    }

    //�f�X�|�[��
    deathpawn_(timer,cannotSpawnTwoItems);
}

//�`��
void Item::Draw_(Player* player)
{
    ++blinkcount_;
    //�I�[�o�[�t���[�΍�
    if (blinkcount_ > 60)
    {
        blinkcount_ = standardNumber;
    }

    if (canExsist_)
    {
        if (blinkcount_ < 30)//�_�ł����Ėڗ�������
        {
            if (position_.y < player->Getposition_().y)
            {
                DrawGraph(chanceGraphPosition.x, chanceGraphPosition.y + 700, chanceGraph_, TRUE);
            }
            else
            {
                DrawGraph(chanceGraphPosition.x, chanceGraphPosition.y, chanceGraph_, TRUE);
            }
            
        }
        MV1DrawModel(modelHandle_);
    }
}

//�ړ�
void Item::move_(Player* player)
{
    //�E�ړ�
    if (isMovingRight_)
    {
        position_.x    += speedX_;
        isMovingLeft_ = false;
        //��ʊO�ɏo���瓮�����t�ɂ���
        if (position_.x > turnMovingPosition_)
        {
            isMovingRight_  = false;
            isMovingLeft_   = true;
        }
    }
    else//���ړ�
    {
        position_.x -= speedX_;
        isMovingRight_ = false;
        //��ʊO�ɏo���瓮�����t�ɂ���
        if (position_.x < -turnMovingPosition_)
        {
            isMovingRight_  = true;
            isMovingLeft_   = false;
        }
    }

    //�A�C�e�������ɂ����ăv���C���[�Ƃ̋���������Ă���Ƃ��͑�������
    if (speedY_ > standardNumber && position_.y - player->Getposition_().y < -70)
    {
        position_.y += speedY_ * 3;
    }
    //�v���C���[�ɂ������Ƃ���y���x�͂������ɂ���
    else if (position_.y - player->Getposition_().y < 50 || position_.y - player->Getposition_().y > -50)
    {
        position_.y += speedY_ / 10;
    }
    else
    {
        position_.y += speedY_;
    }
    
    //�f�o�b�O�p
    //DrawFormatString(500, 100, GetColor(255, 255, 255), "%f", position_.y);
}

//�X�|�[��
void Item::spawn_(Timer* timer, bool& cannotSpawnTwoItems)
{
    if (canRollRandom_)
    {
        //�X�|�[���̃^�C�~���O�ɂȂ�����m��������
        if (timer->GetsecondsTimer_() == spawnRange || timer->GetsecondsTimer_() == spawnRange * 2 || timer->GetsecondsTimer_() == spawnRange * 3)
        {
            randomSpawn_    = GetRand(percentage_);
            canRollRandom_  = false;

            //�o���m�����o���m�����Ⴉ������X�|�[��������
            if (randomSpawn_ < spawnpercentage_ && !canExsist_ && !cannotSpawnTwoItems)
            {
                canExsist_          = true;
                cannotSpawnTwoItems = true;
            }
        }
    }
}

//�|�W�V�������Z�b�g
void Item::resetPosition_(Player* player)
{
    position_ = VAdd(player->Getposition_(), spawnPosition_);
}

//�����蔻��(�蔲���Ȃ̂ŗ]�T������΋��ƃJ�v�Z���̓����蔻��ɂ���)
bool Item::takeItemJudge_(Player* player,Effect* effect)
{
    if (position_.x - hitBoxX_ <= player->Getposition_().x
        && player->Getposition_().x <= position_.x + hitBoxX_
        && position_.y - hitBoxY_ <= player->Getposition_().y
        && player->Getposition_().y <= position_.y + hitBoxY_ - 3)
    {
         effect->UpdateItemGet_(player);
         PlaySoundMem(getItemSound_, DX_PLAYTYPE_BACK, TRUE);
         onDictionary_ = true;
        return false;
    }

    return true;
}

//�A�C�e���̌���
void Item::itemEffect_()
{
    effectCount_ = maxEffectCount_;
}

//�A�C�e�����ʃA�C�R���`��
void Item::DrawEffectIcon_()
{
    if (effectCount_ > standardNumber)
    {
        DrawExtendGraph(minimumIconPositionX_, minimumIconPositionY_, maxIconPositionX_, maxIconPositionY_, icon_, TRUE);
    }
}

//�A�C�e���J�E���g����
void Item::decreseEffectCount_()
{
    if (effectCount_ > standardNumber)
    {
        --effectCount_;
    }
}

//�f�X�|�[��
void Item::deathpawn_(Timer*  timer, bool& cannotSpawnTwoItems)
{
    //�m�����Ăщ񂹂�悤�ɂ���(2�񂾂�)
    if (timer->GetsecondsTimer_() == spawnRange * 3 - 1 || timer->GetsecondsTimer_() == spawnRange * 2 - 1 || timer->GetsecondsTimer_() == spawnRange - 1)
    {
        canRollRandom_ = true;
        cannotSpawnTwoItems = false;
    }

    //�o�������莞�Ԃ�������o���t���O��false�ɂ���B
    if (timer->GetsecondsTimer_() == spawnRange - deleteTime || timer->GetsecondsTimer_() == spawnRange * 2 - deleteTime
        || timer->GetsecondsTimer_() == spawnRange * 3 - deleteTime || timer->GetsecondsTimer_() == spawnRange * 4)
    {
        canExsist_ = false;

        //���ł�60�b�ɂȂ����u�Ԃɏ�����������
        if (timer->GetsecondsTimer_() == spawnRange * 4)
        {
            effectCount_ = standardNumber;
        }
    }
}