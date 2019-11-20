#pragma once
#include"../main.h"

enum DecorationID{RED_BALL, NUM_ITEM};		//デコレーションの種類を判別に使用	最終IDはITEMの種類用のダミー

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
	float picUpDistans;		//拾うことができるようになるまでの距離
	XFILE mesh;
	DecorationID decorationID;
private:
	
	D3DXMATRIX mat;
	D3DXVECTOR3 pos;
	bool picUpFlag;			//拾える状態か
};