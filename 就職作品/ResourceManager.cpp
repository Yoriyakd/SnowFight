#include "ResourceManager.h"

void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color);
void DrawMesh(XFILE *XFile);				//Drawはここじゃない	後で移動させる
void LoadMesh(struct XFILE *XFile, const char FName[]);
void ReleaseMesh(struct XFILE *XFile);



ResourceManager::~ResourceManager()
{
	AllDelete();
}



XFILE ResourceManager::GetXFILE(std::string FileName)
{
	XFILE Tmp;

	Tmp = XFILEList[FileName];

	if (Tmp.lpMesh == nullptr)		//見つからなかったら
	{
		//ロードする
		LoadMesh(&Tmp, &FileName[0]);

		//リストに登録する
		XFILEList[FileName] = Tmp;
	}
	return Tmp;
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTexture(std::string FileName, int width, int hight, D3DCOLOR ColorKey)
{
	LPDIRECT3DTEXTURE9 Tmp;

	//Tmp にmapの値(図の右側)を入れる			Filenameがキーの指定
	Tmp = TextureList[FileName];

	if (Tmp == nullptr)		//Tmpが空(見つからなかったら)
	{
		//テクスチャをロードする
		LoadTexture(&Tmp, &FileName[0], width, hight, ColorKey);
		
		//引数で渡されたFileNameのところにTmpに入ったテクスチャを入れる
		TextureList[FileName] = Tmp;
		
	}
	return Tmp;
}

void ResourceManager::AllDelete(void)
{
	for (auto ite = XFILEList.begin()  ; ite != XFILEList.end()  ; ite++)
	{
		ReleaseMesh(&ite->second);
	}

	XFILEList.clear();

	//型推論 auto
	for (auto ite = TextureList.begin(); ite != TextureList.end(); ite++)
	{
		ite->second->Release();
		//その項目の値(図の右側)
	}
	TextureList.clear();
}





void LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}

void DrawMesh(XFILE *XFile)
{
	for (DWORD i = 0; i < XFile->NumMaterial; i++)
	{
		lpD3DDevice->SetMaterial(&(XFile->Mat[i]));
		lpD3DDevice->SetTexture(0, XFile->Tex[i]);
		XFile->lpMesh->DrawSubset(i);
	}
}

void LoadMesh(struct XFILE *XFile, const char FName[])
{
	LPD3DXBUFFER lpD3DXBuffer;

	D3DXLoadMeshFromX(FName, D3DXMESH_MANAGED, lpD3DDevice, NULL, &lpD3DXBuffer, NULL, &(XFile->NumMaterial), &(XFile->lpMesh));

	XFile->Mat = new D3DMATERIAL9[XFile->NumMaterial];
	XFile->Tex = new LPDIRECT3DTEXTURE9[XFile->NumMaterial];

	D3DXMATERIAL* D3DXMat = (D3DXMATERIAL*)lpD3DXBuffer->GetBufferPointer();

	DWORD i;
	for (i = 0; i < XFile->NumMaterial; i++) {
		XFile->Mat[i] = D3DXMat[i].MatD3D;
		XFile->Mat[i].Ambient = XFile->Mat[i].Diffuse;
		if (FAILED(D3DXCreateTextureFromFile(lpD3DDevice, D3DXMat[i].pTextureFilename, &(XFile->Tex[i])))) {
			XFile->Tex[i] = NULL;
		}
	}

	lpD3DXBuffer->Release();
}

void ReleaseMesh(struct XFILE *XFile)
{
	if (XFile->lpMesh != NULL) {
		DWORD i;

		delete[] XFile->Mat;
		for (i = 0; i < XFile->NumMaterial; i++) {
			if (XFile->Tex[i] != NULL) {
				XFile->Tex[i]->Release();
				XFile->Tex[i] = NULL;
			}
		}
		delete[] XFile->Tex;
		XFile->lpMesh->Release();

		XFile->lpMesh = NULL;
	}
}