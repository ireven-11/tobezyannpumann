#pragma once

#define winmainSetting HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define gameRoopSetting ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0

int  setScreen();   //��ʐݒ�
int  setEffekseer();//�G�t�F�N�V�A�ݒ�
void setFPS();      //fps�ݒ�