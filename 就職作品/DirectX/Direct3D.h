#pragma once
#include"../SingletonBase.h"
#include<d3dx9.h>
#include"../main.h"

// direct3D�֌W�̃N���X�A�V���O���g��
class Direct3D : public SingletonBase<Direct3D>
{
	friend class SingletonBase<Direct3D>;		//SingletonBase�ł̃C���X�^���X���͋���
public:
	// �`��n��ݒ�
	bool InitDirect3D(void);

	// �`��f�o�C�X�������Ă���
	const LPDIRECT3DDEVICE9& GetD3DDevice(void);

	// ���b�V����`��
	void DrawMesh(const XFILE* XFILE);

private:
	//�O���ŃC���X�^���X���֎~
	Direct3D();
	~Direct3D();

	// �`��n�̍���
	LPDIRECT3D9	lpD3D = nullptr;

	// �`��n�̃f�o�C�X
	LPDIRECT3DDEVICE9 lpD3DDevice = nullptr;
};