#include "Decoration_RedBall.h"

Decoration_RedBall::Decoration_RedBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_RedBall_M);
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = RED_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);
	
	moveVec = D3DXVECTOR3(0, 0, 0);
}

Decoration_RedBall::Decoration_RedBall(const ThrowingInitValue *ThrowingInitValue)
{
	mesh = GetResource.GetXFILE(Decoration_RedBall_M);
	pos = ThrowingInitValue->shootPos;

	picUpDistans = 8.0f;
	decorationID = RED_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ŽËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_RedBall::~Decoration_RedBall()
{
}

void Decoration_RedBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
