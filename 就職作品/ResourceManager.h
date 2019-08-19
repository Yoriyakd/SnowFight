#pragma once
#include"main.h"
#include<string>
#include<map>



class ResourceManager
{
private:
	std::map<std::string, XFILE> XFILEList;
	std::map<std::string, LPDIRECT3DTEXTURE9> TextureList;

public:
	
	~ResourceManager();

	//�t�@�C�������w��
	XFILE			  GetXFILE  (std::string FileName);

	//�t�@�C�������w��,  ����,   ����,  �J���[�L�[
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
	
	void AllDelete(void);
};

extern ResourceManager *resourceManager;		//�����ɏ����Ă����v���낤���H