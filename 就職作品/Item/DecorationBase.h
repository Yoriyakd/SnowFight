#pragma once
#include"../main.h"

enum DecorationID{RED_BALL, BLUE_BALL, GREEN_BALL, NUM_ITEM};		//�f�R���[�V�����̎�ނ𔻕ʂɎg�p	�ŏIID��ITEM�̎�ޗp�̃_�~�[

class DecorationBase {
public:
	virtual void Draw();
	virtual bool CheckForCanPicUp(const D3DXVECTOR3 *_Pos);
	void Updata();
	D3DXVECTOR3 GetPos();
	void SetPos(D3DXVECTOR3 *_Pos);
	bool GetPicUpFlag(void);
	DecorationID GetID(void);
protected:
	float picUpDistans;		//�E�����Ƃ��ł���悤�ɂȂ�܂ł̋���
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	DecorationID decorationID;
private:
	bool picUpFlag;			//�E�����Ԃ�
};