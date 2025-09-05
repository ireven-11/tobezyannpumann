#pragma once

const float hitBoxX = 6.00f;    //当たり判定ｘ
const float hitBoxY = 5.00f;    //当たり判定ｙ

class Player;
class Bird;
class Effect;

bool hit(Player* player, Bird* bird[], Effect* effect);         //当たったかの判定
bool superJump(Player* player, Bird* bird[], Effect* effect);   //スーパージャンプの当たり判定