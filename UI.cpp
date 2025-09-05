#include<cmath>
#include<iostream>
#include"DxLib.h"
#include"UI.h"
#include"common.h"
#include"player.h"
#include"selectScene.h"
#include"Windows.h"
#include"timer.h"
#include"bird.h"
#include"rocket.h"
#include"cupCake.h"
#include"wing.h"
#include"shield.h"
#include"ufo.h"
#include"sandClock.h"
#include"routine.h"
#include"player.h"
using namespace std;

const float oneChargeGage = maxSuperJumpCount / 5;

//コンストラクタ
UI::UI()
{
	AddFontResourceEx("font/TenhamasenFontVer.3-Regular.otf", FR_PRIVATE, NULL);
	fontSize100_		= CreateFontToHandle("Tenhamasen Font Ver.3", 100, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontSize150_		= CreateFontToHandle("Tenhamasen Font Ver.3", 150, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontSize75_			= CreateFontToHandle("Tenhamasen Font Ver.3", 75, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontSize125_		= CreateFontToHandle("Tenhamasen Font Ver.3", 125, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontSize40_			= CreateFontToHandle("Tenhamasen Font Ver.3", 40, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	fontSize200_		= CreateFontToHandle("Tenhamasen Font Ver.3", 200, 0, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	enterkeyGraph_		= LoadGraph("img/enter.png");
	spacekeyGraph_		= LoadGraph("img/space.png");
	controlkeyGraph_	= LoadGraph("img/control.png");
	rightkeyGraph_		= LoadGraph("img/migiyazirusi.png");
	leftkeyGraph_		= LoadGraph("img/hidariyazirusi.png");
	upkeyGraph_			= LoadGraph("img/ueyazirusi.png");
	downkeyGraph_		= LoadGraph("img/sitayazirusi.png");
	staminaGraph_		= LoadGraph("img/stamina.png");
	upGraph_			= LoadGraph("img/up.png");
	angle_				= standardSpeed;
	radarGraph_			= LoadGraph("img/radar.png");
	arrowGraph_			= LoadGraph("img/arrow.png");
	birdGraph_			= LoadGraph("img/bird.png");
	shortest_			= standardNumber;
	itemNumber_			= standardNumber;
	for (int i = 0; i < maxBirdNumber; i++)
	{
		distance_[i] = standardNumber;
	}
	dictionaryGraph_	= LoadGraph("img/dictionary2.png");
	isPrevRightAndLeftKey_ = false;
	flipSound_			= LoadSoundMem("sound/flipbook.mp3");
	ChangeVolumeSoundMem(255, flipSound_);
	staminaRedGage_		= LoadGraph("img/redcircle.png");
	rota_ = floatStandardNumber;
	LoadDivGraph("img/yellowarrow.png", 5, 1, 5, 484, 170, chargeArrow_);
	trampleonGraph_		= LoadGraph("img/fumu.png");
	emptyChargeGage_	= LoadGraph("img/siroarrow.png");
}

//デストラクタ
UI::~UI()
{
	// フォントハンドルを削除
	DeleteFontToHandle(fontSize100_);
	DeleteFontToHandle(fontSize150_);
	DeleteFontToHandle(fontSize75_);
	DeleteFontToHandle(fontSize125_);
	DeleteFontToHandle(fontSize40_);
	DeleteFontToHandle(fontSize200_);

	// ウィンドウズに一時的に保持していたフォントデータを削除
	RemoveFontResourceExA("font/TenhamasenFontVer.3-Regular.otf", FR_PRIVATE, NULL);

	//画像削除
	DeleteGraph(enterkeyGraph_);
	DeleteGraph(spacekeyGraph_);
	DeleteGraph(controlkeyGraph_);
	DeleteGraph(rightkeyGraph_);
	DeleteGraph(leftkeyGraph_);
	DeleteGraph(upkeyGraph_);
	DeleteGraph(downkeyGraph_);
	DeleteGraph(staminaGraph_);
	DeleteGraph(upGraph_);
	DeleteGraph(radarGraph_);
	DeleteGraph(arrowGraph_);
	DeleteGraph(birdGraph_);
	DeleteGraph(dictionaryGraph_);
	DeleteGraph(staminaRedGage_);

	DeleteSoundMem(flipSound_);
}

//タイトルUI
void UI::drawTitleUI(SelectScene* selectScene)
{
	DrawStringToHandle(titlePositionX, titlePositionY, "飛べ！ジャンプマン！", GetColor(255, 255, 255), fontSize125_);

	if (selectScene->GetsceneNumber_() == 0)
	{
		DrawStringToHandle(textPlayPositionX, textPlayPositionY, "play", GetColor(255, 50, 50), fontSize75_);
		DrawStringToHandle(textDictionary.x, textDictionary.y, "itemDictionary", GetColor(255, 255, 255), fontSize75_);
		DrawStringToHandle(textCreditsPositionX-10, textCreditsPositionY, "Tutorial", GetColor(255, 255, 255), fontSize75_);
	}
	else if (selectScene->GetsceneNumber_() == 1)
	{
		DrawStringToHandle(textPlayPositionX, textPlayPositionY, "play", GetColor(255, 255, 255), fontSize75_);
		DrawStringToHandle(textDictionary.x, textDictionary.y, "itemDictionary", GetColor(255, 50, 50), fontSize75_);
		DrawStringToHandle(textCreditsPositionX-10, textCreditsPositionY, "Tutorial", GetColor(255, 255, 255), fontSize75_);
	}
	else
	{
		DrawStringToHandle(textPlayPositionX, textPlayPositionY, "play", GetColor(255, 255, 255), fontSize75_);
		DrawStringToHandle(textDictionary.x, textDictionary.y, "itemDictionary", GetColor(255, 255, 255), fontSize75_);
		DrawStringToHandle(textCreditsPositionX-10, textCreditsPositionY, "Tutorial", GetColor(255, 50, 50), fontSize75_);
	}

	//操作方法UI
	DrawExtendGraph(minimumEnterkeyPositionX, minimumEnterkeyPositionY, maxEneterkeyPositionX, maxEneterkeyPositionY, enterkeyGraph_, TRUE);
	DrawStringToHandle(textDicidePositionX, textDicidePositionY, ":決定", GetColor(255, 255, 255), fontSize40_);
	DrawExtendGraph(minimumUpdownkeyPositionX, minimumUpkeyPositionY, maxUpdownkeyPositionX, maxUpkeyPositionY, upkeyGraph_, TRUE);
	DrawExtendGraph(minimumUpdownkeyPositionX, minimumDownkeyPositionY, maxUpdownkeyPositionX, maxDownkeyPositionY, downkeyGraph_, TRUE);
	DrawStringToHandle(textSelectPositionX, textSelectPositionY, ":選択", GetColor(255, 255, 255), fontSize40_);
}

//プレイUI
void UI::drawPlayUI(Timer* timer, Player* player, int staminaRedGage, Bird* bird[])
{
	//ワールド座標をスクリーン画像に変更
	VECTOR tmp = ConvWorldPosToScreenPos(player->Getposition_());

	DrawFormatStringToHandle(textElevationPositionX, textElevationPositionY, GetColor(230, 230, standardNumber), fontSize75_, "標高:%.0fM", player->Getposition_().y * 2);
	DrawFormatStringToHandle(textTimelimitPositionX, textTimelimitPositionY, GetColor(230, 230, standardNumber), fontSize75_, "残り:%d秒", timer->GetsecondsTimer_());

	//操作方法UI
	DrawExtendGraph(minimumControlkeyPositionX, minimumPlayingkeyPositionY, maxControlkeyPositionX, maxPlayingkeyPositionY, controlkeyGraph_, TRUE);
	DrawStringToHandle(textPausePositionX, textPlayingkeyPositionY, ":ポーズ", GetColor(255, 255, 255), fontSize40_);
	DrawExtendGraph(minimumLeftkeyPositionX, minimumPlayingkeyPositionY, maxLeftkeyPositionX, maxPlayingkeyPositionY, leftkeyGraph_, TRUE);
	DrawExtendGraph(minimumRightkeyPositionX, minimumPlayingkeyPositionY, maxRightkeyPositionX, maxPlayingkeyPositionY, rightkeyGraph_, TRUE);
	DrawStringToHandle(textMovePositionX, textPlayingkeyPositionY, ":移動", GetColor(255, 255, 255), fontSize40_);
	DrawExtendGraph(minimumSpacekeyPositionX, minimumPlayingkeyPositionY, maxSpacekeyPositionX, maxPlayingkeyPositionY, spacekeyGraph_, TRUE);
	DrawStringToHandle(textJumpPositionX, textPlayingkeyPositionY, ":ジャンプ", GetColor(255, 255, 255), fontSize40_);

	//プレイヤーui
	DrawCircle(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, radian + 5, GetColor(255, 255, 255), TRUE);
	DrawCircle(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, radian, GetColor(100, 255, 100), TRUE);
	DrawCircleGauge(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, player->Getstamina_(), staminaRedGage_, 0.0f, 1.0f, 200, 200);
	DrawExtendGraph(tmp.x - 170, tmp.y - 235, tmp.x - 130, tmp.y - 165, staminaGraph_, TRUE);
	chargeGage_(player);
	radar_(player, bird);

	//踏む誘導
	for (int i = 0; i < 4; i++)
	{
		DrawBillboard3D(VGet(bird[i]->Getposition_().x, bird[i]->Getposition_().y + 10,floatStandardNumber), 0.5f, 0, 20, 0, trampleonGraph_, TRUE);
	}
}

//クリア画面UI
void UI::drawClearUI(SelectScene* selectScene, Player* player)
{
	DrawStringToHandle(textHighjumpPositionX, textHighjumpPositionY, "跳躍！！", GetColor(255, 255, 255), fontSize150_);
	DrawFormatStringToHandle(textClearSceneElevationPositionX, textClearSceneElevationPositionY, GetColor(230, 230, standardNumber), fontSize75_, "標高:%.0fM", player->Getposition_().y * 2);
	if (selectScene->GetsceneNumber_() == 0)
	{
		DrawStringToHandle(clearsceneTextPositionX, textClearsceneRetryPositionY, "retry", GetColor(255, 0, 0), fontSize75_);
		DrawStringToHandle(clearsceneTextPositionX, textClearsceneReturntotitlePositionY, "return to title", GetColor(255, 255, 255), fontSize75_);
	}
	else
	{
		DrawStringToHandle(clearsceneTextPositionX, textClearsceneRetryPositionY, "retry", GetColor(255, 255, 255), fontSize75_);
		DrawStringToHandle(clearsceneTextPositionX, textClearsceneReturntotitlePositionY, "return to title", GetColor(255, 0, 0), fontSize75_);
	}
}

//ポーズUI
void UI::drawPauseUI(SelectScene* selectScene)
{
	++brinkCounter_;

	if (maxBrinkCounter / 2 > brinkCounter_)
	{
		DrawStringToHandle(textPauseScenePausePositionX, textPauseScenePausePositionY, "PAUSE", GetColor(255, 255, 255), fontSize150_);
	}

	//カウンターを戻す
	if (brinkCounter_ == maxBrinkCounter)
	{
		brinkCounter_ = standardNumber;
	}

	if (selectScene->GetsceneNumber_() == 0)
	{
		DrawStringToHandle(textReturntoplayPositionX, textReturntoplayPositionY, "return to play", GetColor(255, 50, 0), fontSize100_);
		DrawStringToHandle(textPausesceneRetryPositionX, textPausesceneRetryPositionY, "retry", GetColor(255, 255, 255), fontSize100_);
		DrawStringToHandle(textPausesceneReturntotitlePositionX, textPausesceneReturntotitlePositionY, "return to title", GetColor(255, 255, 255), fontSize100_);
	}
	else if (selectScene->GetsceneNumber_() == 1)
	{
		DrawStringToHandle(textReturntoplayPositionX, textReturntoplayPositionY, "return to play", GetColor(255, 255, 255), fontSize100_);
		DrawStringToHandle(textPausesceneRetryPositionX, textPausesceneRetryPositionY, "retry", GetColor(255, 50, 0), fontSize100_);
		DrawStringToHandle(textPausesceneReturntotitlePositionX, textPausesceneReturntotitlePositionY, "return to title", GetColor(255, 255, 255), fontSize100_);
	}
	else
	{
		DrawStringToHandle(textReturntoplayPositionX, textReturntoplayPositionY, "return to play", GetColor(255, 255, 255), fontSize100_);
		DrawStringToHandle(textPausesceneRetryPositionX, textPausesceneRetryPositionY, "retry", GetColor(255, 255, 255), fontSize100_);
		DrawStringToHandle(textPausesceneReturntotitlePositionX, textPausesceneReturntotitlePositionY, "return to title", GetColor(255, 50, 0), fontSize100_);
	}
}

//ready?UI
void UI::drawReadyUI()
{
	++brinkCounter_;

	DrawStringToHandle(textReadyPositionX, textReadyPositionY, "READY?", GetColor(255, 255, 255), fontSize150_);

	//点滅描画
	if (maxBrinkCounter / 2 > brinkCounter_)
	{
		DrawStringToHandle(textEntertostartPositionX, textEntertostartPositionY, "enterでスタート", GetColor(255, 255, 255), fontSize40_);
	}

	//ゲーム目標テキスト描画
	DrawStringToHandle(textGameTargetPositionX, textGameTargetPositionY, "はるか上空を目指せ！", GetColor(255, 50, 0), fontSize75_);
	DrawExtendGraph(minimumUpGraphPositionX, minimumUpGraphPositionY, maxUpGraphPositionX, maxUpGraphPositionY, upGraph_, TRUE);

	//カウンターを戻す
	if (brinkCounter_ == maxBrinkCounter)
	{
		brinkCounter_ = standardNumber;
	}
}

//finishUI
void UI::finishUI_(Timer* timer)
{
	//クリアした時だけ出す
	if (timer->GetsecondsTimer_() <= standardNumber || CheckHitKey(KEY_INPUT_1) == 1)
	{
		DrawStringToHandle(screenWIDTH / 3, screenHEIGHT / 3, "Finish!", GetColor(255, 255, 255), fontSize200_);
	}
}

//レーダーUI
void UI::radar_(Player* player, Bird* bird[])
{
	//プレイヤーとの距離が一番近い鳥を調べる
	for (int i = 0; i < maxBirdNumber; i++)
	{
		distance_[i] = player->Getposition_().y - bird[i]->Getposition_().y;

		//絶対値をはかる
		if (distance_[i] < floatStandardNumber/*(0.0f)*/)
		{
			distance_[i] *= -1;
		}

		//一番近い鳥のｘ座標を参照して回転角度を決める
		if (distance_[i] <= distance_[shortest_])
		{
			shortest_ = i;
		}
	}

	//アークタンジェントで角度を求める
	angle_ = atan2(bird[shortest_]->Getposition_().y - player->Getposition_().y, bird[shortest_]->Getposition_().x - player->Getposition_().x);

	//描画
	VECTOR PlayerToBird = VSub(bird[shortest_]->Getposition_(), player->Getposition_());
	PlayerToBird = VScale(VNorm(PlayerToBird), 20.0f);
	VECTOR tmp = VAdd(player->Getposition_(), PlayerToBird);
	DrawBillboard3D(VGet(tmp.x, tmp.y + 7.5f, tmp.z), 0.5, 0.5, 7, angle_, arrowGraph_, TRUE);
}

//アイテム説明UI
void UI::explain3DItemUI_(int nameX, int nameY, const char* name, int nameColor, int nameFont,
	int itemModel, VECTOR itemPosition, int effectX, int effectY, const char* effect, int effectColor, int effectFont)
{
	//名前を描画
	DrawStringToHandle(nameX, nameY, name, nameColor, nameFont);

	rota_ += 0.5;
	if (rota_ > 360.0f)
	{
		rota_ = floatStandardNumber;
	}

	//3dモデルを描画
	MV1SetScale(itemModel, VGet(0.13f, 0.13f, 0.13f));
	MV1SetRotationXYZ(itemModel, VGet(floatStandardNumber, (340.00f+rota_) * DX_PI_F / 180.00f, floatStandardNumber));
	MV1SetPosition(itemModel, itemPosition);
	MV1DrawModel(itemModel);

	//アイテム効果を描画
	DrawStringToHandle(effectX, effectY, effect, effectColor, effectFont);
}

//アイテムを選ぶ
void UI::selectItem_()
{
	if (CheckHitKey(KEY_INPUT_RIGHT) == TRUE)
	{
		if (!isPrevRightAndLeftKey_)
		{
			++itemNumber_;
			PlayMovie("video/flipleft1.mp4",1,DX_PLAYTYPE_NORMAL);
			PlaySoundMem(flipSound_, DX_PLAYTYPE_BACK, TRUE);
			if (itemNumber_ >= maxItemNumber)
			{
				itemNumber_ = standardNumber;
			}
		}
		isPrevRightAndLeftKey_ = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT) == TRUE)
	{
		if (!isPrevRightAndLeftKey_)
		{
			--itemNumber_;
			PlayMovie("video/flipright1.mp4", 1, DX_PLAYTYPE_NORMAL);
			PlaySoundMem(flipSound_, DX_PLAYTYPE_BACK, TRUE);

			if (itemNumber_ < standardNumber)
			{
				itemNumber_ = maxItemNumber - 1;
			}
		}
		isPrevRightAndLeftKey_ = true;
	}
	else
	{
		isPrevRightAndLeftKey_ = false;
	}
}

void UI::dictionaryUI()
{
	DrawExtendGraph(minimumEnterkeyPositionX, minimumEnterkeyPositionY, maxEneterkeyPositionX, maxEneterkeyPositionY, enterkeyGraph_, TRUE);
	DrawStringToHandle(textDicidePositionX, textDicidePositionY, ":戻る", GetColor(255, 255, 255), fontSize40_);
	DrawExtendGraph(minimumLeftkeyPositionX - 250, minimumPlayingkeyPositionY - 80, maxLeftkeyPositionX - 250, maxPlayingkeyPositionY - 80, leftkeyGraph_, TRUE);
	DrawExtendGraph(minimumRightkeyPositionX - 250, minimumPlayingkeyPositionY - 80, maxRightkeyPositionX - 250, maxPlayingkeyPositionY - 80, rightkeyGraph_, TRUE);
	DrawStringToHandle(textMovePositionX - 250, textPlayingkeyPositionY - 80, ":前,次のページへ", GetColor(255, 255, 255), fontSize40_);
}

//チュートリアルui
void UI::tutorialUI_(Player* player, Bird* bird[], Routine* routine)
{
	DrawStringToHandle(textTutorial.x, textTutorial.y, "「チュートリアル」", GetColor(255, 255, 255), fontSize100_);
	DrawExtendGraph(minimumEnterkeyPositionX, minimumEnterkeyPositionY, maxEneterkeyPositionX, maxEneterkeyPositionY, enterkeyGraph_, TRUE);
	DrawStringToHandle(textDicidePositionX, textDicidePositionY, ":本番へ", GetColor(255, 255, 255), fontSize40_);

	if (routine->GetisTutorial1_())
	{
		DrawStringToHandle(textTutorial.x - 400, textTutorial.y + 150, "1:スペースを長押ししてためジャンプしてみよう。\n押してる長さでジャンプの距離が変わるぞ。ためジャンプはスタミナを消費するので注意だ", GetColor(255, 255, 255), fontSize40_);
	}
	else if (routine->GetisTutorial2_())
	{
		DrawStringToHandle(textTutorial.x - 375, textTutorial.y + 150, "2:ためジャンプは空中でもできる。やってみよう", GetColor(255, 255, 255), fontSize75_);
	}
	else if (routine->GetisTutorial3_())
	{
		DrawStringToHandle(textTutorial.x - 100, textTutorial.y + 150, "3:左右十字キーで移動してみよう", GetColor(255, 255, 255), fontSize75_);
	}
	else if (routine->GetisTutorial4_())
	{
		DrawStringToHandle(textTutorial.x - 100, textTutorial.y + 150, "4:鳥を踏むとスタミナを使わずにジャンプできる。やってみよう", GetColor(255, 255, 255), fontSize40_);
	}
	else if (routine->GetisTutorial5_())
	{
		DrawStringToHandle(textTutorial.x - 100, textTutorial.y + 150, "5:アイテムをとってみよう。アイテムには様々な効果がある。\nタイトルのアイテム図鑑で効果を確認できるぞ", GetColor(255, 255, 255), fontSize40_);
		DrawStringToHandle(textTutorial.x - 100, textTutorial.y + 300, "申し訳ありません。時間が足りずここだけ実装できていません。\nエンターを押してプレイへお進み下さい", GetColor(255, 0, 0), fontSize40_);
	}

	//プレイヤーui
	VECTOR tmp = ConvWorldPosToScreenPos(player->Getposition_());
	DrawCircle(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, radian + 5, GetColor(255, 255, 255), TRUE);
	DrawCircle(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, radian, GetColor(100, 255, 100), TRUE);
	DrawCircleGauge(tmp.x - shiftStaminaGraph.x, tmp.y - shiftStaminaGraph.y, player->Getstamina_(), staminaRedGage_);
	DrawExtendGraph(tmp.x - 170, tmp.y - 235, tmp.x - 130, tmp.y - 165, staminaGraph_, TRUE);
	radar_(player, bird);
	chargeGage_(player);
}

//チャージゲージ
void UI::chargeGage_(Player* player)
{
	//ワールド座標をスクリーン画像に変更
	VECTOR tmp = ConvWorldPosToScreenPos(player->Getposition_());

	//チャージゲージ（空）
	DrawExtendGraph(tmp.x + emptyArrowShift.x, tmp.y + emptyArrowShift.y,
		tmp.x + emptyArrowWidth + emptyArrowShift.x, tmp.y + emptyArrowHeight + emptyArrowShift.y,
		emptyChargeGage_, TRUE);
	DrawExtendGraph(tmp.x + emptyArrowShift.x, tmp.y + emptyArrowShift.y * 5,
		tmp.x + emptyArrowWidth + emptyArrowShift.x, tmp.y + emptyArrowHeight + emptyArrowShift.y * 5,
		emptyChargeGage_, TRUE);

	//チャージゲージ（ため）
	if (player->GetmaxNormalJumpCount_() > floatStandardNumber)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * 3,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * 3,
			chargeArrow_[4], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * 2,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * 2,
			chargeArrow_[3], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 2)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y,
			chargeArrow_[2], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 3)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * 0,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * 0,
			chargeArrow_[1], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 4)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -1,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -1,
			chargeArrow_[0], TRUE);
		
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 5)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -2,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -2,
			chargeArrow_[4], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 6)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -3,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -3,
			chargeArrow_[3], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 7)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -4,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -4,
			chargeArrow_[2], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 8)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -5,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -5,
			chargeArrow_[1], TRUE);
	}
	if (player->GetmaxNormalJumpCount_() > oneChargeGage * 9)
	{
		DrawExtendGraph(tmp.x + chargeArrowShift.x, tmp.y + chargeArrowShift.y * -6,
			tmp.x + chargeArrowWidth + chargeArrowShift.x, tmp.y + chargeArrowHeight + chargeArrowShift.y * -6,
			chargeArrow_[0], TRUE);
	}
}