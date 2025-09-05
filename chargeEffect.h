#pragma once

class Player;

class ChargeEffect
{
public:
	ChargeEffect();
	~ChargeEffect();

	void Draw_(Player* player);
	void Update_(Player* player);
	void UpdateCount_();

private:
	int handle_;
	VECTOR position_;
	int playingHandle_;
	int count_;
	const int maxCount_ = 140;
	bool canStart_;
	bool canStartCount_;
};