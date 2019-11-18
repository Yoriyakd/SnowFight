#pragma once
#include<d3dx9.h>
#include"../main.h"
class PlayerCamera {
public:
	PlayerCamera(int, int, HWND);
	~PlayerCamera();
	void Update(void);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetbillBoardMat(void);
	D3DXVECTOR3 GetmoveVec(void);
	D3DXVECTOR3 GetPos(void);
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);

private:
	//--------------------------------------------------
	//�}�E�X�ŃJ�����𓮂����p�̕ϐ��Q
	//--------------------------------------------------
	HWND hwnd;
	POINT basePt;
	int SCRw, SCRh;		//�X�N���[���̃T�C�Y�ۑ��p
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	float moveSpeed;
	
	const float camHight = 5.0f;		//�J������y0����̍���


	D3DXMATRIX billBoardMat;		//������r���{�[�h�̍s������Ă���
	D3DXVECTOR3 moveVec;		//�ړ��x�N�g����ۑ����Ă������莞�ɓn��
	//--------------------------------------------------
	//���\�b�h
	//--------------------------------------------------
	void Move(void);

};

extern LPDIRECT3DDEVICE9 lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X