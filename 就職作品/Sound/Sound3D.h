#pragma once
#include"Sound2D.h"
class Sound3D : public Sound2D {
public:
	Sound3D();
	~Sound3D();
private:
	//���W�Ƃ���3D�悤�f�[�^
	LPDIRECTSOUND3DBUFFER8 Buffer3D;
};