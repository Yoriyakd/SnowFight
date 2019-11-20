#pragma once
#include<vector>
#include"DecorationBase.h"
#include"Decoration_Ball.h"
class ItemManager {
public:
	ItemManager();
	~ItemManager();
	std::vector<DecorationBase*> decoration;
	bool CheckForCanPicUp(const D3DXVECTOR3 *_Pos);
	DecorationID PickUpItem(const D3DXVECTOR3 *_Pos);
	void Draw(void);
	void Updata(void);
private:
};