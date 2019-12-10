#pragma once
#include"../main.h"

enum DecorationID{RED_BALL, BLUE_BALL, YELLOW_BALL, NUM_ITEM};		//デコレーションの種類を判別に使用	最終IDはITEMの種類用のダミー

//------------------------------------------------------------------------
//デコレーションの基底クラス継承して使う
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
	D3DXVECTOR3 GetMoveVec();				//グローバルの移動ベクトルを渡す

	void SetDecoratedState(bool);					//状態を更新
	bool GetDecoratedState(void);				//状態を返す

	void PushPos(D3DXVECTOR3 *PushVec);		//埋まってい分押し出すときに使う
protected:
	float picUpDistans;		//拾うことができるようになるまでの距離
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	DecorationID decorationID;
	D3DXVECTOR3 moveVec;
private:
	bool picUpFlag;			//拾える状態か
	bool decoratedState;		//飾られているか　trueなら飾られていて動かない
	D3DXVECTOR3 memoryPos, globalMoveVec;
};