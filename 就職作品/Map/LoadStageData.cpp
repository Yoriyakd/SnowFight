#include "LoadStageData.h"

//===============================================
//public
//===============================================



LoadStageData::LoadStageData(int StageNo)
{
	nowStageNo = StageNo;
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

void LoadStageData::SetStageMap(MapObjManager * MapObjManager)
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

	int BenchCnt, TreeCnt, XmasTreeCnt;

	fscanf_s(fp, "Bench:%d\n", &BenchCnt);

	for (int i = 0; i <= BenchCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager->SetBench(TmpPos, TmpAng);
	}

	fscanf_s(fp, "Tree:%d\n", &TreeCnt);

	for (int i = 0; i <= TreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		float TmpAng;
		fscanf_s(fp, "%f,%f,%f:%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z, &TmpAng);
		MapObjManager->SetTree(TmpPos, TmpAng);
	}

	fscanf_s(fp, "XmasTree:%d\n", &XmasTreeCnt);

	for (int i = 0; i <= XmasTreeCnt; i++)
	{
		D3DXVECTOR3 TmpPos;
		fscanf_s(fp, "%f,%f,%f\n", &TmpPos.x, &TmpPos.y, &TmpPos.z);
		MapObjManager->SetXmasTree(TmpPos);
	}


	fclose(fp);


	//int a;
	//fscanf(fp, "��:%d\n", &a);		//�V�[�N�ʒu�͓ǂ񂾂��ƈړ�����
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		�o�C�i���^���ł���K�v������
//	fread(b, sizeof(b), 1, fp);			�o�C�i���^����


}



