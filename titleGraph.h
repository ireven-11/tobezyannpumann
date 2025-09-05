#pragma once

const int jumpUp                = 3;    //�W�����v�㏸��
const int randomJump            = 250;  //�W�����v�ʁi�����_���j
const int jumpmanWIDTHHEIGHT    = 100;  //�W�����v�}���̕��ƍ���

class TitleGraph
{
public:
	TitleGraph();
	~TitleGraph();
    
    void Update_();
    void Draw_();
    void InitFlag_();

private:
    int  titleGraph_;           //�^�C�g���摜
    int  cloud_[3];             //��
    int  random_     = 0;       //�����_��
    bool isRandom_   = false;   //�������邩�t���O
    int  shift_      = 0;       //���炵��
    int  graph1x1_, graph1x2_;  //�摜�P�̂����W
    int  graph2x1_, graph2x2_;  //�摜2�̂����W
    int  jumpGraph_;            //�W�����v�摜
    int  jumpX_;                //�W�����v��
    int  jumpY_;                //�W�����v��
    int  jumpCount_;            //�W�����v�J�E���g
    int  maxJumpCount_;         //�ő�l�W�����v�J�E���g
};

