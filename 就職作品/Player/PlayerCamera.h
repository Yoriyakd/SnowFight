#pragma once
#include<d3dx9.h>
#include"../main.h"
#include"../SingletonBase.h"
//----------------------------------------
//�v���C���[�̃J�����N���X
//�ړ��⎋�_�����S��
//----------------------------------------

#define GetPlayerCam PlayerCamera::GetInstance()

class PlayerCamera : public SingletonBase<PlayerCamera>{
	friend class SingletonBase<PlayerCamera>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	void Update(StageBorder & StageBorder);
	void SetCamera(void);
	//--------------------------------------------------
	//Getter
	//--------------------------------------------------
	float GetCamAngX(void);
	float GetCamAngY(void);
	D3DXMATRIX GetmView(void);
	D3DXVECTOR3 GetmoveVec(void);					//�v���C���[�̈ړ��x�N�g����Ԃ�
	D3DXVECTOR3 GetPos(void);
	bool GetHasPosed(void);				//�p���ύX����������������
	//--------------------------------------------------
	//Setter
	//--------------------------------------------------
	void PushPos(D3DXVECTOR3 *PushVec);				//�����o���x�N�g����^����(�����蔻��̂Ƃ���Ŏg��)
	void SetPos(D3DXVECTOR3 *SetPos);
	void SetMakeSnowBallFlag(bool Flag);			//
	void SetMoveSpeed(float MoveSpeed);				//�ړ����x��ύX����

private:
	PlayerCamera();
	~PlayerCamera();
	//--------------------------------------------------
	//�}�E�X�ŃJ�����𓮂����p�̕ϐ��Q
	//--------------------------------------------------
	POINT basePt;
	//--------------------------------------------------
	float angX, angY;
	D3DXMATRIX rotMatY, rotMatX, rotMat;
	D3DXVECTOR3 pos;
	//-------------------------------------------------
	//�ݒ�p�̕ϐ�(�����̒l��ύX����)
	//-------------------------------------------------
	float moveSpeed = 0.5f;		//�ړ����x
	const float CAM_HIGHT = 5.0f;		//�J������y0����̍���
	const float MAKEBALL_CAM_ANG = 50.0f;	//��ʍ쐬���̃J�����̊p�x
	const float SQUAT_SPEED = 0.2f;			//��ʍ쐬���̂��Ⴊ�ރX�s�[�h
	//-------------------------------------------------

	D3DXMATRIX billBoardMat;		//������r���{�[�h�̍s������Ă���
	D3DXVECTOR3 moveVec;		//�ړ��x�N�g����ۑ����Ă������莞�ɓn��
	D3DXMATRIX mView, mProj;		//���_�s��,���e�s��

	bool MakeSnowBallFlag;		//true�̎���ʍ쐬�̎p���ɂȂ�
	bool hasPosed;				//�p���ύX���I��������̃t���O
	float mouseSensitivityX = 1.0f, mouseSensitivityY = 1.0f;			//�}�E�X���x�����p�ϐ�
	//--------------------------------------------------
	//���\�b�h
	//--------------------------------------------------
	void Move(StageBorder &StageBorder);
	bool MakeSnowBallPose(void);

};