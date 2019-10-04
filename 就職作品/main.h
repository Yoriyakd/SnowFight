#pragma once
#include<d3dx9.h>


extern LPDIRECT3D9				lpD3D;		// Direct3Dインターフェイス
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern D3DPRESENT_PARAMETERS d3dpp;
extern HWND hwnd;
extern int FPS;

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height


#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


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

enum ID{PLAYER_ID, ENEMY_ID};

struct SnowBallInitValue {
	D3DXVECTOR3 shootPos;
	float XAxisAng;
	float YAxisAng;
	float powerRate;
	ID id;
};

struct CollisionSphere {
	D3DXVECTOR3 pos;
	float radius;
};

void DrawMesh(XFILE *XFile);

bool CollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB);

bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis);