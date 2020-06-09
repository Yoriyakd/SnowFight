#include"Decoration_YellowBall.h"

const float Decoration_YellowBall::YELLOW_PIC_UP_RANGE = 8.0f;

Decoration_YellowBall::Decoration_YellowBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = *_Pos;

	decorationID = YELLOW_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);

	moveVec = D3DXVECTOR3(0, 0, 0);		//0‰Šú‰»
}

Decoration_YellowBall::Decoration_YellowBall(const ThrowingInitValue * ThrowingInitValue)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = ThrowingInitValue->shootPos;

	decorationID = YELLOW_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_YellowBall::~Decoration_YellowBall()
{
}

float Decoration_YellowBall::GetCanPicUpRange()
{
	return YELLOW_PIC_UP_RANGE;
}
