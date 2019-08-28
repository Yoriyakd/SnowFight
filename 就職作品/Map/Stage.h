#pragma once
#include"Ground.h"
#include"../Enemy/Enemy.h"
#include<vector>
class Stage {
private:
	static const int stageX = 10;		//�}�b�v�̃T�C�Y�̉���(�l�͉��̂���)
	static const int stageY = 10;		//�}�b�v�̃T�C�Y�̏c��(�l�͉��̂���)
	int StageMap[stageX][stageY];		//�X�e�[�W�̃I�u�W�F�N�g�̔ԍ������ă}�b�v����肽��
	int enemyNum, wallNum;				//�X�e�[�W���̃I�u�W�F�N�g�̐�������
	int nowStageNo;						//�X�e�[�WNo.���Q�Ƃ���Ƃ��Ɏg��

	FILE *fp;							//�I�[�v�������t�@�C���̃|�C���^
	

	std::vector <Enemy*> enemy;
	
	void SetStageMap(void);				//text�t�@�C�����J���ă}�b�v�����
	
	//char��int�ɕϊ��@�߂�l�͕ϊ���������Ԃ��@0�`9�ȊO��-999��Ԃ�
	int ctoi(char c);					


public:
	Stage(int);		//stageNo������
	~Stage();
	void Draw();
};