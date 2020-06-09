#include "Decoration_BlueBall.h"

const float Decoration_BlueBall::BLUE_PIC_UP_RANGE = 8.0f;

Decoration_BlueBall::Decoration_BlueBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_BlueBall_M);
	pos = *_Pos;

	decorationID = BLUE_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);

	moveVec = D3DXVECTOR3(0, 0, 0);		//0‰Šú‰»
}

Decoration_BlueBall::Decoration_BlueBall(const ThrowingInitValue *ThrowingInitValue)
{

	mesh = GetResource.GetXFILE(Decoration_BlueBall_M);
	pos = ThrowingInitValue->shootPos;

	decorationID = BLUE_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_BlueBall::~Decoration_BlueBall()
{
}

float Decoration_BlueBall::GetCanPicUpRange()
{
	return BLUE_PIC_UP_RANGE;
}

