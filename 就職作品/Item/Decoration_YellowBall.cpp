#include"Decoration_YellowBall.h"

Decoration_YellowBall::Decoration_YellowBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = YELLOW_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);

	moveVec = D3DXVECTOR3(0, 0, 0);
}

Decoration_YellowBall::Decoration_YellowBall(const ThrowingInitValue * ThrowingInitValue)
{
	mesh = GetResource.GetXFILE(Decoration_YellowBall_M);
	pos = ThrowingInitValue->shootPos;

	picUpDistans = 8.0f;
	decorationID = YELLOW_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ŽËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_YellowBall::~Decoration_YellowBall()
{
}

void Decoration_YellowBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}