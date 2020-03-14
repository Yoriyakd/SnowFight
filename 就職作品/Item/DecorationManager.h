#pragma once
#include<vector>
#include"../SingletonBase.h"
#include"DecorationBase.h"
#include"Decoration_RedBall.h"
#include"Decoration_BlueBall.h"
#include"Decoration_YellowBall.h"

#define GetDecorationManager DecorationManager::GetInstance() 

class DecorationManager : public SingletonBase<DecorationManager>{
	friend class SingletonBase<DecorationManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	
	void DeleteToResult(void);
	std::vector<DecorationBase*> decoration;

	void NewDecoration(D3DXVECTOR3 *_Pos, CarryObjectID CarryObjectID);

	bool CheckForCanPicUp(const D3DXVECTOR3 *_Pos);
	CarryObjectID PickUp(const D3DXVECTOR3 *_Pos);
	void Throw(CarryObjectID ID, ThrowingInitValue * ThrowingInitValue);

	void Draw(void);
	void Updata(void);
private:
	DecorationManager();
	~DecorationManager();
};