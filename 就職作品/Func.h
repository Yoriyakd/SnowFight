#pragma once
#include<d3dx9.h>
#include"StructDefinition.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス


void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);

void DrawMesh(XFILE *XFile);

void LoadMesh(struct XFILE *XFile, const char FName[]);

void ReleaseMesh(struct XFILE *XFile);

template <class T>

inline void SafeRelease(T & lpAdd)
{
	if (lpAdd != nullptr)
	{
		lpAdd->Release();
		lpAdd = nullptr;
	}
}