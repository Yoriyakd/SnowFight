#pragma once
#include"PlayerStateBase.h"
class ThrowState :public PlayerStateBase {
public:
	ThrowState(void);
	PlayerStateBase* Anime(D3DXMATRIX *NowMatL, D3DXMATRIX *NowMatR);
private:
	float atOneceRot, endAng, nowAng;		//1�x�ɉ�]����p�x		�I���̊p�x	���݂̊p�x
	const float shootAng;							//�肩��ˏo����p�x(��ʂ������^�C�~���O�̊p�x)
};
