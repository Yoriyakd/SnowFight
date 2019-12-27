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

class ResourceManager : public SingletonBase<ResourceManager>
{
public:
	friend class SingletonBase<ResourceManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���

	//�t�@�C�������w��
	XFILE			  GetXFILE(std::string FileName);

	//�t�@�C�������w��,  ����,   ����,  �J���[�L�[
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
protected:

private:
	ResourceManager();
	~ResourceManager();

	std::map<std::string, XFILE> XFILEList;				//�|�C���^�^�Ő錾����悤�ɕς���		�|�C���^�^�Ő錾�����ꍇ���̃|�C���^�ϐ��̍폜���K�v
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);
};

ResourceManager* SingletonBase<ResourceManager>::instance = nullptr;		//nullptr�ŏ�����(DirectX�̋@�\���g������DirectX��������ɍ쐬����K�v������)static�ōŏ��Ɋm�ۂ���Ă�����͂ǂ���...?�������ĂȂ��������邼