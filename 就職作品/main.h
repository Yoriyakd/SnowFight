#pragma once
#include<d3dx9.h>

#define GAME_FPS 60		//������ӂ̒萔�f�[�^�Ƃ����܂Ƃ߂����Ǘ��N���X�Ƃ�������ق��������񂾂낤��

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

//�����𔭎˂���Ƃ��ɓn���f�[�^�̍\����
struct ThrowingInitValue {
	D3DXVECTOR3 shootPos;		//�ł��o���ʒu
	float XAxisAng;				//X���̉�]�p�x	*Degree�œn��
	float YAxisAng;				//Y���̉�]�p�x	*Degree�œn��
	float powerRate;			//�ł��o���p���[�̊���	*0~100
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

enum CollisionDetectionType{Ray, Circles};

void DrawMesh(XFILE *XFile);

//�����m�̓����蔻��
bool SphereCollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB);

//���b�V���ɑ΂��Ẵ��C����(MeshDis��PolyNo��nullptr���e)		HIT���Ȃ������ꍇMeshDis�ɂ�-1������
bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis, DWORD *PolyNo);

//ThrowingInitValue��n���ƈړ��x�N�g�����Ԃ��Ă��Ĕ��ˈʒu�̍s��쐬���ł���
D3DXVECTOR3 ThrowingInit(const ThrowingInitValue* ThrowingInitValue, D3DXMATRIX *Mat);

//�N�I�[�^�j�I���ŃA�j���[�V��������֐�	�������ɉ��H�����s�񂪓���
void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame);

//���_�s���n���ăr���{�[�h�s����쐬
void MakeBillBoardMat(D3DXMATRIX *OutMat, const D3DXMATRIX *_mView);

//�����œn���ꂽ�S�����̒l������true�ɂȂ邩��Ԃ�
bool IsOverProbabilityValue(const int& Probability);