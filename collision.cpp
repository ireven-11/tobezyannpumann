#include"DxLib.h"
#include"common.h"
#include"collision.h"
#include"player.h"
#include"bird.h"
#include"effect.h"

//�����������ǂ�������
bool hit(Player* player,Bird* bird[],Effect* effect)
{
    for (int i = 0; i < maxBirdNumber; i++)
    {
        //�����蔻��
        if (player->Getposition_().x - hitBoxX <= bird[i]->Getposition_().x
            && bird[i]->Getposition_().x <= player->Getposition_().x + hitBoxX
            && player->Getposition_().y - hitBoxY <= bird[i]->Getposition_().y
            && bird[i]->Getposition_().y <= player->Getposition_().y + hitBoxY * 2)
        {
            return true;
        }
    }

    return false;
}

//�X�[�p�[�W�����v�̓����蔻��(�o�O����)
bool superJump(Player* player, Bird* bird[],Effect* effect)
{
    for (int i = 0; i < maxBirdNumber; i++)
    {
        //�����蔻��
        if (bird[i]->Getposition_().x - hitBoxX * 2 <= player->Getposition_().x
            && player->Getposition_().x <= bird[i]->Getposition_().x + hitBoxX
            && bird[i]->Getposition_().y + hitBoxY - 4.9f <= player->Getposition_().y
            && player->Getposition_().y <= bird[i]->Getposition_().y + hitBoxY * 2 - 3
            /*&& player->GetisFall_()*/)
        {
            effect->UpdateSuperJump_(bird, i);
            return true;
        }
    }

    return false;
}