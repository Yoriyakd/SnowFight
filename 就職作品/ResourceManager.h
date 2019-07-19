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

	//ファイル名を指定
	XFILE			  GetXFILE  (std::string FileName);

	//ファイル名を指定,  横幅,   高さ,  カラーキー
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey);
	
	void AllDelete(void);
};
