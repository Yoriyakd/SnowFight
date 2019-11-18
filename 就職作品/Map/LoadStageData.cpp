#include "LoadStageData.h"

//const float LoadStageData::TILE_SIZE = 18.0f;				//�錾���������ł��Ȃ��̂ł����ŏ�����
//===============================================
//public
//===============================================



LoadStageData::LoadStageData(int StageNo)
{
	nowStageNo = StageNo;
	SetStageMap();
}

LoadStageData::~LoadStageData()
{

}


void LoadStageData::GetStageSize(float *StageSizeX, float *StageSizeZ)
{
	*StageSizeX = stageSizeX;
	*StageSizeZ = stageSizeZ;
}


//===============================================
//private
//===============================================

void LoadStageData::SetStageMap(void)
{
	char FileName[16];
	//=================================================================================
	//�t�@�C���I�[�v��
	//=================================================================================

	sprintf_s(FileName, sizeof(FileName), "data/stage%d.txt", nowStageNo);		//�t�@�C���p�X�쐬

	fopen_s(&fp, FileName, "r");	//fopen�̃Z�L�����e�B�����ł炵��


	////=================================================================================
	////�ǂݎ�����l���Z�b�g
	////=================================================================================
	fscanf_s(fp, "StageSizeX:%f\n", &stageSizeX);
	fscanf_s(fp, "StageSizeY:%f\n", &stageSizeZ);

	fclose(fp);


	//int a;
	//fscanf(fp, "��:%d\n", &a);		//�V�[�N�ʒu�͓ǂ񂾂��ƈړ�����
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		�o�C�i���^���ł���K�v������
//	fread(b, sizeof(b), 1, fp);			�o�C�i���^����


}



