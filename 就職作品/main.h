#pragma once
#include<d3dx9.h>


extern LPDIRECT3D9				lpD3D;		// Direct3D�C���^�[�t�F�C�X
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern D3DPRESENT_PARAMETERS d3dpp;
extern HWND hwnd;
extern int FPS;

#define	SCRW		1280	// �E�B���h�E���iWidth
#define	SCRH		720		// �E�B���h�E�����iHeight


#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


// ���_�t�H�[�}�b�g�̒�`
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};


//X�t�@�C���̒�`
struct XFILE {
	LPD3DXMESH lpMesh;			//mesh�̌`��f�[�^	
	DWORD NumMaterial;			//�O���[�v�̐�
	D3DMATERIAL9 *Mat;			//�}�e���A���̓��e�@* �O���[�v����
	LPDIRECT3DTEXTURE9 *Tex;	//Texture�̓��e * �O���[�v����		
};

enum ID{PLAYER_ID, ENEMY_ID};

struct SnowBallInitValue {
	D3DXVECTOR3 shootPos;
	float XAxisAng;
	float YAxisAng;
	float powerRate;
	ID id;
};

void DrawMesh(XFILE *XFile);

bool CollisionDetection(D3DXVECTOR3 PosA, float radiusA, D3DXVECTOR3 PosB, float radiusB);