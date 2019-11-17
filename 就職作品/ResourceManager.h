#pragma once
#include"main.h"
#include<string>
#include<map>



class ResourceManager
{
private:
	std::map<std::string, XFILE> XFILEList;				//�|�C���^�^�Ő錾����悤�ɕς���		�|�C���^�^�Ő錾�����ꍇ���̃|�C���^�ϐ��̍폜���K�v
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;
	void AllDelete(void);
public:
	
	~ResourceManager();

	//�t�@�C�������w��
	XFILE			  GetXFILE  (std::string FileName);

	//�t�@�C�������w��,  ����,   ����,  �J���[�L�[
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
	
};

extern ResourceManager *resourceManager;		//main�Ő錾