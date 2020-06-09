#pragma once
#include"../main.h"

enum CarryObjectID{RED_BALL, BLUE_BALL, YELLOW_BALL, SNOW_BALL, STAR, NUM_ITEM_Dummy};		//デコレーションの種類を判別に使用	最終IDはITEMの種類用のダミー

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

	//デコレーションが飾られる状態になった際呼び出す関数
	void DoDecorate(const D3DXVECTOR3 &TreeVec);
	void PushPos(const D3DXVECTOR3 &PushVec);		//埋まってい分押し出すときに使う
protected:
	virtual float GetCanPicUpRange() = 0;		//拾うことができるようになるまでの距離	それぞれの派生に定数で距離を持たせるのは効率の面でいいのだろうか？
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

	static const D3DXVECTOR3 GROUND_GRIP;

	void Move();
	void DecorateEffect();
};