#pragma once

#include"../main.h"

class XFILEObject {
protected :
	XFILE mesh;
	D3DXMATRIX mat;
public:
	void Draw(void);
};