#include"DxLib.h"
#include"setting.h"
#include"common.h"
#include"EffekseerForDXLib.h"

//��ʐݒ�
int setScreen()
{
    ChangeWindowMode(TRUE);				        //�E�B���h�E���[�h�ɂ���
    SetWindowStyleMode(7);				        //�ő剻�{�^�������݂���E�C���h�E���[�h�ɕύX
    SetWindowSizeChangeEnableFlag(TRUE, FALSE); //�T�C�Y�ύX���\�ɂ���
    SetWindowSize(screenWIDTH, screenHEIGHT);   //�E�C���h�E�T�C�Y�̓Q�[����ʂƈ�v������
    SetMainWindowText("��ׁI�W�����v�}���I");	//���O���Z�b�g
    SetDrawScreen(DX_SCREEN_FRONT);		        //�w�i���Z�b�g����
    SetGraphMode(screenWIDTH, screenHEIGHT, 32);//�E�B���h�E�̃T�C�Y�ƃJ���[���[�h�����߂�

	//���C�u�����������ŃG���[�N������I��
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	return 0;
}

//�G�t�F�N�V�A�ݒ�
int setEffekseer()
{
	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(8000) == -1)
	{
		/*return -1;*/
	}

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Effekseer��2D�`��̐ݒ������B(��ʂ̕��ƍ����������Ƃ��Ď�������)
	//Effekseer_Set2DSetting(screenWIDTH, screenHEIGHT);

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	return 0;
}

//fps�ݒ�
void setFPS()
{
	//�����̕����̐��l�𑝂₷�قǂ��������������Ă���
	const int fps = 32;

	int term;
	static int t = standardNumber;
	term = GetNowCount() - t;
	if (fps - term > standardNumber)
		Sleep(fps - term);
	t = GetNowCount();
}