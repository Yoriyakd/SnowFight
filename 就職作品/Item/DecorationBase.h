#pragma once
#include"../main.h"

enum CarryObjectID{RED_BALL, BLUE_BALL, YELLOW_BALL, SNOW_BALL, NUM_ITEM_Dummy};		//�f�R���[�V�����̎�ނ𔻕ʂɎg�p	�ŏIID��ITEM�̎�ޗp�̃_�~�[

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
	void SetMoveVec(const D3DXVECTOR3 &_Vec);

	//Getter
	D3DXVECTOR3 GetPos();
	bool GetPicUpFlag(void);
	CarryObjectID GetID(void);
	D3DXVECTOR3 GetMoveVec();				//�O���[�o���̈ړ��x�N�g����n��

	//�f�R���[�V�����̏��
	void SetDecoratedState(bool);					//��Ԃ��X�V
	bool GetDecoratedState(void);				//��Ԃ�Ԃ�

	//�f�R���[�V����������̏�ԂɂȂ����یĂяo���֐�
	void DoDecorate(const D3DXVECTOR3 &TreeVec);
	void PushPos(const D3DXVECTOR3 &PushVec);		//���܂��Ă��������o���Ƃ��Ɏg��
protected:
	float picUpDistans;		//�E�����Ƃ��ł���悤�ɂȂ�܂ł̋���
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	CarryObjectID decorationID;
	D3DXVECTOR3 moveVec;
	float decorationRadius;		//�c���[���痣������
private:
	bool canPicUp;			//�E�����Ԃ�
	bool isDecorated;		//�����Ă��邩�@true�Ȃ�����Ă��ē����Ȃ�
	bool doDecoratFlag;
	D3DXVECTOR3 memoryPos, globalMoveVec;

	void Move();
	void DecorateEffect();
};