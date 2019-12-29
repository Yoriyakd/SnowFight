#pragma once
#include"main.h"
#include<string>
#include<map>
#include"SingletonBase.h"

//------------------------------------------------------------------------------------------------
//���V���O���g���N���X
//�}�N����`��GetResource���C���X�^���X�Q�ƂɂȂ��Ă���
//XFILE�ƃX�v���C�g���Ǘ�����N���X
//------------------------------------------------------------------------------------------------

#define GetResource ResourceManager::GetInstance()

enum MeshName
{
	ArmL_M,
	ArmR_M,
	Bench_M,
	BenchCollision_M,
	Bobbin_Red_M,
	Decoration_RedBall_M,
	Decoration_BlueBall_M,
	Decoration_YellowBall_M,
	EnemyBody_M,
	EnemyHat_M,
	Kamakura_M,
	Shoes_M,
	SnowBall_M,
	Sky_M,
	Tree_M,
	XmasTree_M
};

enum TexName
{

};

class ResourceManager : public SingletonBase<ResourceManager>
{
public:
	friend class SingletonBase<ResourceManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	//enum�Œ�`���ꂽMeshName������
	XFILE			  GetXFILE(enum MeshName);

	//�t�@�C�������w��,  ����,   ����,  �J���[�L�[
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
protected:

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, XFILE> XFILEList;				//�|�C���^�^�Ő錾����悤�ɕς���		�|�C���^�^�Ő錾�����ꍇ���̃|�C���^�ϐ��̍폜���K�v
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);

	std::map<MeshName, std::string> MeshFileName{
		{ArmL_M,                  "ArmL.x"},
		{ArmR_M,                  "ArmR.x"},
		{Bench_M,                 "Bench.x"},
		{BenchCollision_M,        "BenchCollision.x"},
		{Bobbin_Red_M,            "Bobbin_Red.x"},
		{Decoration_RedBall_M,    "Decoration_RedBall.x"},
		{Decoration_BlueBall_M,   "Decoration_BlueBall.x"},
		{Decoration_YellowBall_M, "Decoration_YellowBall.x"},
		{EnemyBody_M,             "EnemyBody.x"},
		{EnemyHat_M,              "EnemyHat.x"},
		{Kamakura_M,              "Kamakura.x"},
		{Shoes_M,                 "Shoes.x"},
		{SnowBall_M,              "SnowBall.x"},
		{Sky_M,                   "Sky.x"},
		{Tree_M,                  "Tree.x"},
		{XmasTree_M,              "XmasTree.x"}
	};
};

ResourceManager* SingletonBase<ResourceManager>::instance = nullptr;		//nullptr�ŏ�����(DirectX�̋@�\���g������DirectX��������ɍ쐬����K�v������)static�ōŏ��Ɋm�ۂ���Ă�����͂ǂ���...?�������ĂȂ��������邼

