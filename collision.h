#pragma once

const float hitBoxX = 6.00f;    //�����蔻�肘
const float hitBoxY = 5.00f;    //�����蔻�肙

class Player;
class Bird;
class Effect;

bool hit(Player* player, Bird* bird[], Effect* effect);         //�����������̔���
bool superJump(Player* player, Bird* bird[], Effect* effect);   //�X�[�p�[�W�����v�̓����蔻��