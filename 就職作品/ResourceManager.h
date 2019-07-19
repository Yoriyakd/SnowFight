#pragma once
#include"StructDefinition.h"
#include<string>
#include<map>

extern LPDIRECT3DDEVICE9		lpD3DDevice;

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
