#pragma once
#include"../main.h"

enum CarryObjectID{RED_BALL, BLUE_BALL, YELLOW_BALL, SNOW_BALL, NUM_ITEM_Dummy};		//デコレーションの種類を判別に使用	最終IDはITEMの種類用のダミー

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
	void SetMoveVec(const D3DXVECTOR3 &_Vec);

	//Getter
	D3DXVECTOR3 GetPos();
	bool GetPicUpFlag(void);
	CarryObjectID GetID(void);
	D3DXVECTOR3 GetMoveVec();				//グローバルの移動ベクトルを渡す

	//デコレーションの状態
	void SetDecoratedState(bool);					//状態を更新
	bool GetDecoratedState(void);				//状態を返す

	//デコレーションが特定の状態になった際呼び出す関数
	void DoDecorate(const D3DXVECTOR3 &TreeVec);
	void PushPos(const D3DXVECTOR3 &PushVec);		//埋まってい分押し出すときに使う
protected:
	float picUpDistans;		//拾うことができるようになるまでの距離
	D3DXVECTOR3 pos;
	D3DXMATRIX mat;
	XFILE mesh;
	CarryObjectID decorationID;
	D3DXVECTOR3 moveVec;
	float decorationRadius;		//ツリーから離す距離
private:
	bool canPicUp;			//拾える状態か
	bool isDecorated;		//飾られているか　trueなら飾られていて動かない
	bool doDecoratFlag;
	D3DXVECTOR3 memoryPos, globalMoveVec;

	void Move();
	void DecorateEffect();
};