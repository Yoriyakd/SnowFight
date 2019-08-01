#pragma once
#include<d3dx9.h>


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

