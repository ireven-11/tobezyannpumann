#pragma once

const int maxPauseSceneNumber = 2;//�|�[�Y��ʂ̍ő�V�[���i���o�[
const int maxOtherSceneNumber = 1;//����ʂ̍ő�V�[���i���o�[

class SelectScene
{
public:
	SelectScene();	//�R���X�g���N�^
	~SelectScene();	//�f�X�g���N�^

	void Update(int sceneType);	//�X�V
	void Init_();				//������

	int GetsceneNumber_()const { return sceneNumber_; }

private:
	int		sceneNumber_	= 0;	//�V�[���i���o�[
	int		maxSceneNumber_	= 2;	//�ő�V�[���i���o�[
	bool	isPrevButton_	= false;//�{�^���������h���t���O
	int		selectSound_;			//�Z���N�g�T�E���h
};