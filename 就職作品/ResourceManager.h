#pragma once
#include"StructDefinition.h"
#include<string>
#include<map>

extern LPDIRECT3DDEVICE9		lpD3DDevice;

class ResourceManager
{
private:
	std::map<std::string, XFILE> XFILEList;

public:
	~ResourceManager();


};
