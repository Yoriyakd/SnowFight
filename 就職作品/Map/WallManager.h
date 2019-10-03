#pragma once
#include<vector>
#include"Wall.h"

class WallManager {
private:
public:
	std::vector<Wall*> wall;

	WallManager();
	~WallManager();

	void SetWall(D3DXVECTOR3 Pos);

	void Draw();
	void Update();
};
