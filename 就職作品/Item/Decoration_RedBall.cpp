#include "Decoration_RedBall.h"

const float Decoration_RedBall::RED_PIC_UP_RANGE = 8.0f;

Decoration_RedBall::Decoration_RedBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_RedBall_M);
	pos = *_Pos;

	decorationID = RED_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);
	
	moveVec = D3DXVECTOR3(0, 0, 0);		//0‰Šú‰»
}

Decoration_RedBall::Decoration_RedBall(const ThrowingInitValue *ThrowingInitValue)
{
	mesh = GetResource.GetXFILE(Decoration_RedBall_M);
	pos = ThrowingInitValue->shootPos;

	decorationID = RED_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_RedBall::~Decoration_RedBall()
{
}

float Decoration_RedBall::GetCanPicUpRange()
{
	return RED_PIC_UP_RANGE;
}
