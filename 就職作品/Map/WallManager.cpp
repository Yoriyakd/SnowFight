#include "WallManager.h"

WallManager::WallManager()
{
}

WallManager::~WallManager()
{
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		delete wall[i];
	}
	wall.clear();
}

void WallManager::SetWall(D3DXVECTOR3 Pos)
{
	wall.push_back(new Wall(Pos));
}

void WallManager::Draw()
{
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		wall[i]->Draw();
	}
}

void WallManager::Update()
{
	for (unsigned int i = 0; i < wall.size(); i++)
	{
		wall[i]->Draw();
	}
}
