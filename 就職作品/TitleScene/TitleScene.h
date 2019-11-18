#pragma once
#include<d3d9.h>
#include"../main.h"
#include"../SceanSwitcher/SceneSwitcher.h"
#include"../ResourceManager.h"

class TitleScene : public SceneBase {
public:
	TitleScene();
	~TitleScene();

	void Render3D(void);
	void SetCamera(void);
	void Render2D(void);
	bool Update(void);

private:
	LPDIRECT3DTEXTURE9 logoTex;
	D3DXMATRIX logoMat;
	const int logoTexX = 832;		//���S��x�����̃T�C�Y	x�����g������ꉞx�����ϐ��ɂ��Ă݂�

	LPDIRECT3DTEXTURE9 backTex;
	D3DXMATRIX backMat;
};
