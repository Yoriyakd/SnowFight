#pragma once
#include"Ground.h"
#include"../Enemy/Enemy.h"
#include<vector>
class StageCreater {
private:
	static const int stageX = 10;		//�}�b�v�̃T�C�Y�̉���(�l�͉��̂���)
	static const int stageY = 10;		//�}�b�v�̃T�C�Y�̏c��(�l�͉��̂���)
	int StageMap[stageX][stageY];		//�X�e�[�W�̃I�u�W�F�N�g�̔ԍ������ă}�b�v����肽��
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��(��������Ȃ�)

	void SetStageMap(int);				//text�t�@�C�����J���ă}�b�v�����


public:
	StageCreater();
	~StageCreater();
	void Draw();
};