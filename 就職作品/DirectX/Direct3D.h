#pragma once
#include"../SingletonBase.h"
#include<d3dx9.h>
#include"../main.h"

// direct3D関係のクラス、シングルトン
class Direct3D : public SingletonBase<Direct3D>
{
	friend class SingletonBase<Direct3D>;		//SingletonBaseでのインスタンス化は許可
public:
	// 描画系を設定
	bool InitDirect3D(void);

	// 描画デバイスを持ってくる
	const LPDIRECT3DDEVICE9& GetD3DDevice(void);

	// メッシュを描画
	void DrawMesh(const XFILE* XFILE);

private:
	//外部でインスタンス化禁止
	Direct3D();
	~Direct3D();

	// 描画系の根幹
	LPDIRECT3D9	lpD3D = nullptr;

	// 描画系のデバイス
	LPDIRECT3DDEVICE9 lpD3DDevice = nullptr;
};