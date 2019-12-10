#pragma once
#include"../main.h"

enum DecorationID{RED_BALL, BLUE_BALL, YELLOW_BALL, NUM_ITEM};		//�f�R���[�V�����̎�ނ𔻕ʂɎg�p	�ŏIID��ITEM�̎�ޗp�̃_�~�[

//------------------------------------------------------------------------
//�f�R���[�V�����̊��N���X�p�����Ďg��
//------------------------------------------------------------------------

class DecorationBase {
public:
	DecorationBase();
	~DecorationBase();
	virtual void Draw();
	virtual bool CheckForCanPicUp(const D3DXVECTOR3 *_Pos);
	void Updata();

	void SetPos(D3DXVECTOR3 *_Pos);
	void SetMoveVec(D3DXVECTOR3 *_Vec);

	D3DXVECTOR3 GetPos();
	bool GetPicUpFlag(void);
	DecorationID GetID(void);
	D3DXVECTOR3 GetMoveVec();				//�O���[�o���̈ړ��x�N�g����n��

	void SetDecoratedState(bool);					//��Ԃ��X�V
	bool GetDecoratedState(void);				//��Ԃ�Ԃ�

	void PushPos(D3DXVECTOR3 *PushVec);		//���܂��Ă��������o���Ƃ��Ɏg��
protected:
	float picUpDistans;		//�E�����Ƃ��ł���悤�ɂȂ�܂ł̋���
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	DecorationID decorationID;
	D3DXVECTOR3 moveVec;
private:
	bool picUpFlag;			//�E�����Ԃ�
	bool decoratedState;		//�����Ă��邩�@true�Ȃ�����Ă��ē����Ȃ�
	D3DXVECTOR3 memoryPos, globalMoveVec;
};