#include "Decoration_Star.h"

Decoration_Star::Decoration_Star(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = STAR;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);

	moveVec = D3DXVECTOR3(0, 0, 0);
}

Decoration_Star::Decoration_Star(const ThrowingInitValue * ThrowingInitValue)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = ThrowingInitValue->shootPos;

	picUpDistans = 8.0f;
	decorationID = STAR;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_Star::~Decoration_Star()
{
}
