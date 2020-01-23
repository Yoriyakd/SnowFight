#pragma once
#include"Sound2D.h"
class Sound3D : public Sound2D {
public:
	Sound3D();
	~Sound3D();
private:
	//座標とかの3Dようデータ
	LPDIRECTSOUND3DBUFFER8 Buffer3D;
};