#pragma once
#include"../main.h"

enum DecorationID{RED_BALL, BLUE_BALL, YELLOW_BALL, NUM_ITEM};		//�f�R���[�V�����̎�ނ𔻕ʂɎg�p	�ŏIID��ITEM�̎�ޗp�̃_�~�[

class DecorationBase {
public:
	virtual void Draw();
	virtual bool CheckForCanPicUp(const D3DXVECTOR3 *_Pos);
	void Updata();

	void SetPos(D3DXVECTOR3 *_Pos);

	D3DXVECTOR3 GetPos();
	bool GetPicUpFlag(void);
	DecorationID GetID(void);
	D3DXVECTOR3 GetMoveVec();				//�O���[�o���̈ړ��x�N�g����n��
protected:
	float picUpDistans;		//�E�����Ƃ��ł���悤�ɂȂ�܂ł̋���
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	DecorationID decorationID;
	D3DXVECTOR3 moveVec;
private:
	bool picUpFlag;			//�E�����Ԃ�
	D3DXVECTOR3 memoryPos, globalMoveVec;
};