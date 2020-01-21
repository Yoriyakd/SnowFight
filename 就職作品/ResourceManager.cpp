#include "ResourceManager.h"

XFILE ResourceManager::GetXFILE(enum MeshName _MeshName)
{
	XFILE TmpXFILE;

	std::string FileName;

	FileName = MeshFileName[_MeshName];

	if (XFILEList.find(FileName) == XFILEList.end())		//最後まで検索する
	{
		std::string FilePath = "data/";
		FilePath += FileName;		//パスの作成
		//ロードする
		LoadMesh(&TmpXFILE, &FilePath[0]);

		LPD3DXMESH TmpMesh;
		TmpXFILE.lpMesh->CloneMeshFVF(D3DXMESH_NPATCHES | D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, lpD3DDevice, &TmpMesh);	//Meshデータを扱いやすい形に変換

		TmpXFILE.lpMesh->Release();

		TmpXFILE.lpMesh = TmpMesh;

		//リストに登録する
		XFILEList[FileName] = TmpXFILE;
	}
	
	return XFILEList[FileName];
}

LPDIRECT3DTEXTURE9 ResourceManager::GetTexture(enum TexName _TexName)
{
	LPDIRECT3DTEXTURE9 Tmp;

	TexData TexData;

	TexData = TexFileName[_TexName];

	if (TextureList.find(TexData.FileName) == TextureList.end())		//最後まで検索する
	{
		std::string FilePath = "data/";
		FilePath += TexData.FileName;		//パスの作成
		//テクスチャをロードする
		LoadTexture(&Tmp, &FilePath[0], TexData.Width, TexData.Hight, TexData.Color);

		//引数で渡されたFileNameのところにTmpに入ったテクスチャを入れる
		TextureList[TexData.FileName] = Tmp;
	}
	
	return TextureList[TexData.FileName];
}

LPDIRECTSOUNDBUFFER8 ResourceManager::GetSound(SoundName _SoundName)
{
	LPDIRECTSOUNDBUFFER8 Tmp;

	std::string FileName;

	FileName = SoundFileName[_SoundName];

	if (SoundBufferList.find(FileName) == SoundBufferList.end())
	{
		std::string FilePath = "data/";
		FilePath += FileName;				//パスの作成

		//ロードする
	LoadWAVE(Tmp, &FilePath[0]);

		SoundBufferList[FileName] = Tmp;
	}
	
	return SoundBufferList[FileName];
}

//-------------------------------------------------------------------
//privateメソッド
//-------------------------------------------------------------------

void ResourceManager::LoadWAVE(LPDIRECTSOUNDBUFFER8 &_Buffer, const char fname[])
{
	HRESULT hr;

	// WAVEファイルを開く
	CWaveSoundRead WaveFile;
	WaveFile.Open((char*)fname);

	// セカンダリ・バッファを作成する
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);

	//(DSBCAPS_CTRL3D=３Ｄサウンドを使用)
	dsbdesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRL3D |
		DSBCAPS_CTRLVOLUME | /*DSBCAPS_CTRLPAN |*/ DSBCAPS_CTRLFREQUENCY;
	dsbdesc.dwBufferBytes = WaveFile.m_ckIn.cksize;
	dsbdesc.lpwfxFormat = WaveFile.m_pwfx;

	//3DサウンドのHELアルゴリズムを選択
	dsbdesc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	//	dsbdesc.guid3DAlgorithm=DS3DALG_DEFAULT;

		// バッファを作る
	LPDIRECTSOUNDBUFFER pDSTmp;
	//	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSData, NULL); 
	lpDSound->CreateSoundBuffer(&dsbdesc, &pDSTmp, NULL);
	pDSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&_Buffer);
	pDSTmp->Release();

	// セカンダリ・バッファにWaveデータを書き込む
	LPVOID lpvPtr1;		// 最初のブロックのポインタ
	DWORD dwBytes1;		// 最初のブロックのサイズ
	LPVOID lpvPtr2;		// ２番目のブロックのポインタ
	DWORD dwBytes2;		// ２番目のブロックのサイズ

	hr = _Buffer->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);

	// DSERR_BUFFERLOSTが返された場合，Restoreメソッドを使ってバッファを復元する
	if (DSERR_BUFFERLOST == hr)
	{
		_Buffer->Restore();
		hr = _Buffer->Lock(0, WaveFile.m_ckIn.cksize, &lpvPtr1, &dwBytes1, &lpvPtr2, &dwBytes2, 0);
	}
	if (SUCCEEDED(hr))
	{
		// ロック成功

		// ここで，バッファに書き込む
		// バッファにデータをコピーする
		UINT rsize;
		WaveFile.Read(dwBytes1, (LPBYTE)lpvPtr1, &rsize);
		if (0 != dwBytes2)
			WaveFile.Read(dwBytes2, (LPBYTE)lpvPtr2, &rsize);

		// 書き込みが終わったらすぐにUnlockする．
		hr = _Buffer->Unlock(lpvPtr1, dwBytes1, lpvPtr2, dwBytes2);
	}
}

void ResourceManager::AllDelete(void)
{
	for (auto ite = XFILEList.begin(); ite != XFILEList.end(); ite++)
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

	for (auto ite = SoundBufferList.begin(); ite != SoundBufferList.end(); ite++)
	{
		ite->second->Release();
		ite->second->Release();
	}
	SoundBufferList.clear();
}

ResourceManager::~ResourceManager()
{
	AllDelete();
}



ResourceManager::ResourceManager()
{

}

void ResourceManager::LoadTexture(LPDIRECT3DTEXTURE9 *lpTex, const char fname[], int W, int H, D3DCOLOR Color)
{
	if (W == 0)W = D3DX_DEFAULT;
	if (H == 0)H = D3DX_DEFAULT;
	D3DXCreateTextureFromFileEx(lpD3DDevice, fname, W, H, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT, Color, NULL, NULL, lpTex);
}



void ResourceManager::LoadMesh(struct XFILE *XFile, const char FName[])
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

void ResourceManager::ReleaseMesh(struct XFILE *XFile)
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
