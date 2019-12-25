#pragma once
#include"main.h"
#include<string>
#include<map>

//------------------------------------------------------------------------------------------------
//���V���O���g���N���X
//�}�N����`��GetResource���C���X�^���X�Q�ƂɂȂ��Ă���
//XFILE�ƃX�v���C�g���Ǘ�����N���X
//------------------------------------------------------------------------------------------------

#define GetResource ResourceManager::GetInstance()

class ResourceManager
{
public:
	static void Create();
	static void Destroy();

	//�t�@�C�������w��
	XFILE			  GetXFILE(std::string FileName);

	//�t�@�C�������w��,  ����,   ����,  �J���[�L�[
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);

	static ResourceManager& GetInstance();

	~ResourceManager();
private:
	ResourceManager();
	
	static ResourceManager *resourceManager;

	std::map<std::string, XFILE> XFILEList;				//�|�C���^�^�Ő錾����悤�ɕς���		�|�C���^�^�Ő錾�����ꍇ���̃|�C���^�ϐ��̍폜���K�v
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);
};
