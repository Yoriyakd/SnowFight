#pragma once
#include"../main.h"
#include"../ResourceManager.h"

struct ButtonData {
	D3DXVECTOR2 Pos;		//���W
	D3DXVECTOR2 BoxSize;	//�N���b�N����̃T�C�Y
};

class ButtonBase {
public:
	ButtonBase(void);
	void Draw();
	void Update();
	bool GetState(void);
protected:
	virtual void OnMouseEvent(void);
	virtual void OffMouseEvent(void);
	
	ButtonData buttonData;
	bool nowStae;		//�J�[�\������ɏ�����Ă�����true
	
};