#pragma once
#include<d3dx9.h>

//クラス設計としていまいちな気がする	このヘッダーを参照していて独立性が下がっている気がする

// 頂点フォーマットの定義
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};


//Xファイルの定義
struct XFILE {
	LPD3DXMESH lpMesh;			//meshの形状データ	
	DWORD NumMaterial;			//グループの数
	D3DMATERIAL9 *Mat;			//マテリアルの内容　* グループ数分
	LPDIRECT3DTEXTURE9 *Tex;	//Textureの内容 * グループ数分		
};

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height
