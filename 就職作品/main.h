#pragma once
#include<d3dx9.h>


extern LPDIRECT3D9				lpD3D;		// Direct3D�C���^�[�t�F�C�X
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g
extern LPD3DXFONT lpFont;		// �t�H���g
extern D3DPRESENT_PARAMETERS d3dpp;
extern HWND hwnd;
extern const int GameFPS;

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

//���b�V���̌`���ȈՉ��̒�`
struct CLONEVERTEX
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 Tex;
};

//��΂�����ʂɕt�^
enum ID{PLAYER_ID, ENEMY_ID};

//��ʂ𔭎˂���Ƃ��ɓn���f�[�^�̍\����
struct SnowBallInitValue {
	D3DXVECTOR3 shootPos;		//�ł��o���ʒu
	float XAxisAng;				//X���̉�]�p�x	*Degree�œn��
	float YAxisAng;				//Y���̉�]�p�x	*Degree�œn��
	float powerRate;			//�ł��o���p���[�̊���	*0~100
	ID id;						//���˂����L������enum�Œ�`����ID������
};

//�����蔻��̋��̏���n�����Ɏg���\����
struct CollisionSphere {
	D3DXVECTOR3 pos;
	float radius;
};

//�X�e�[�W�̋��E�\����
struct StageBorder
{
	float Top;
	float Bottom;
	float Left;
	float Right;
};

//�{�[���f�R���[�V�����̐F		//main.cpp�Œl��������
struct Decoration_BallColor
{
	D3DCOLORVALUE RED_BALL_COLOR;
	D3DCOLORVALUE BLUE_BALL_COLOR;
	D3DCOLORVALUE GREEN_BALL_COLOR;
};

extern Decoration_BallColor decoration_BallColor;		//main.cpp�Ő錾

enum CollisionDetectionType{Ray, Circles};

void DrawMesh(XFILE *XFile);
void DrawMesh(XFILE *XFile, D3DCOLORVALUE Color);

//�����m�̓����蔻��
bool CollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB);

//���b�V���ɑ΂��Ẵ��C����
bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis);

//SnowBallInitValue��n���ƈړ��x�N�g�����Ԃ��Ă��Ĕ��ˈʒu�̍s��쐬���ł���
D3DXVECTOR3 SnowBallInit(SnowBallInitValue* SnowBallInitValue, D3DXMATRIX *Mat);

//�N�I�[�^�j�I���ŃA�j���[�V��������֐�	�������ɉ��H�����s�񂪓���
void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame);