#include"DxLib.h"
#include"item.h"
#include"common.h"
#include"player.h"
#include"effect.h"
#include"timer.h"

//コンストラクタ
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

//デストラクタ
Item::~Item()
{
    MV1DeleteModel(modelHandle_);
    DeleteGraph(icon_);
    DeleteSoundMem(getItemSound_);
}

//更新
void Item::Update_(Timer* timer, bool& cannotSpawnTwoItems,Player* player,Effect* effect)
{
    //アイテムの大きさをセット
    MV1SetScale(modelHandle_, VGet(itemScale_, itemScale_, itemScale_));
    MV1SetRotationXYZ(modelHandle_, VGet(floatStandardNumber, floatStandardNumber, floatStandardNumber));

    if (canExsist_)
    {
        //移動
        move_(player);

        // ３Dモデルのポジション設定
        MV1SetPosition(modelHandle_, position_);

        //プレイヤーとの当たり判定
        canExsist_ = takeItemJudge_(player,effect);

        //キラキラ
        effect->kirakiraCounter_();
        effect->kirakira_(this);

        //アイテムの効果を発動
        if (!canExsist_)
        {
            itemEffect_();
        }
    }
    else
    {
        //アイテムを出現位置に戻す
        resetPosition_(player);
    }

    //デスポーン
    deathpawn_(timer,cannotSpawnTwoItems);
}

//描画
void Item::Draw_(Player* player)
{
    ++blinkcount_;
    //オーバーフロー対策
    if (blinkcount_ > 60)
    {
        blinkcount_ = standardNumber;
    }

    if (canExsist_)
    {
        if (blinkcount_ < 30)//点滅させて目立たせる
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

//移動
void Item::move_(Player* player)
{
    //右移動
    if (isMovingRight_)
    {
        position_.x    += speedX_;
        isMovingLeft_ = false;
        //画面外に出たら動きを逆にする
        if (position_.x > turnMovingPosition_)
        {
            isMovingRight_  = false;
            isMovingLeft_   = true;
        }
    }
    else//左移動
    {
        position_.x -= speedX_;
        isMovingRight_ = false;
        //画面外に出たら動きを逆にする
        if (position_.x < -turnMovingPosition_)
        {
            isMovingRight_  = true;
            isMovingLeft_   = false;
        }
    }

    //アイテムが下にあってプレイヤーとの距離が離れているときは速くする
    if (speedY_ > standardNumber && position_.y - player->Getposition_().y < -70)
    {
        position_.y += speedY_ * 3;
    }
    //プレイヤーにちかいときはy速度はゆっくりにする
    else if (position_.y - player->Getposition_().y < 50 || position_.y - player->Getposition_().y > -50)
    {
        position_.y += speedY_ / 10;
    }
    else
    {
        position_.y += speedY_;
    }
    
    //デバッグ用
    //DrawFormatString(500, 100, GetColor(255, 255, 255), "%f", position_.y);
}

//スポーン
void Item::spawn_(Timer* timer, bool& cannotSpawnTwoItems)
{
    if (canRollRandom_)
    {
        //スポーンのタイミングになったら確率をだす
        if (timer->GetsecondsTimer_() == spawnRange || timer->GetsecondsTimer_() == spawnRange * 2 || timer->GetsecondsTimer_() == spawnRange * 3)
        {
            randomSpawn_    = GetRand(percentage_);
            canRollRandom_  = false;

            //出た確率が出現確率より低かったらスポーンさせる
            if (randomSpawn_ < spawnpercentage_ && !canExsist_ && !cannotSpawnTwoItems)
            {
                canExsist_          = true;
                cannotSpawnTwoItems = true;
            }
        }
    }
}

//ポジションリセット
void Item::resetPosition_(Player* player)
{
    position_ = VAdd(player->Getposition_(), spawnPosition_);
}

//当たり判定(手抜きなので余裕があれば球とカプセルの当たり判定にする)
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

//アイテムの効果
void Item::itemEffect_()
{
    effectCount_ = maxEffectCount_;
}

//アイテム効果アイコン描画
void Item::DrawEffectIcon_()
{
    if (effectCount_ > standardNumber)
    {
        DrawExtendGraph(minimumIconPositionX_, minimumIconPositionY_, maxIconPositionX_, maxIconPositionY_, icon_, TRUE);
    }
}

//アイテムカウント減少
void Item::decreseEffectCount_()
{
    if (effectCount_ > standardNumber)
    {
        --effectCount_;
    }
}

//デスポーン
void Item::deathpawn_(Timer*  timer, bool& cannotSpawnTwoItems)
{
    //確率を再び回せるようにする(2回だけ)
    if (timer->GetsecondsTimer_() == spawnRange * 3 - 1 || timer->GetsecondsTimer_() == spawnRange * 2 - 1 || timer->GetsecondsTimer_() == spawnRange - 1)
    {
        canRollRandom_ = true;
        cannotSpawnTwoItems = false;
    }

    //出現から一定時間たったら出現フラグをfalseにする。
    if (timer->GetsecondsTimer_() == spawnRange - deleteTime || timer->GetsecondsTimer_() == spawnRange * 2 - deleteTime
        || timer->GetsecondsTimer_() == spawnRange * 3 - deleteTime || timer->GetsecondsTimer_() == spawnRange * 4)
    {
        canExsist_ = false;

        //ついでに60秒になった瞬間に初期化もする
        if (timer->GetsecondsTimer_() == spawnRange * 4)
        {
            effectCount_ = standardNumber;
        }
    }
}