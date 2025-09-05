#pragma once

#define winmainSetting HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
#define gameRoopSetting ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0

int  setScreen();   //画面設定
int  setEffekseer();//エフェクシア設定
void setFPS();      //fps設定