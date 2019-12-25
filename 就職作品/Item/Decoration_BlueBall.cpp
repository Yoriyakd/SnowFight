#include "Decoration_BlueBall.h"

Decoration_BlueBall::Decoration_BlueBall(const D3DXVECTOR3 * _Pos)
{
	mesh = GetResource.GetXFILE("Decoration_BlueBall.x");
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = BLUE_BALL;

	D3DXMatrixTranslation(&mat, _Pos->x, _Pos->y, _Pos->z);

	moveVec = D3DXVECTOR3(0, 0, 0);
}

Decoration_BlueBall::Decoration_BlueBall(const D3DXVECTOR3 * _Pos, ThrowingInitValue * ThrowingInitValue)
{

	mesh = GetResource.GetXFILE("Decoration_BlueBall.x");
	pos = *_Pos;

	picUpDistans = 8.0f;
	decorationID = BLUE_BALL;

	moveVec = ThrowingInit(ThrowingInitValue, &mat);

	D3DXMATRIX TmpRot;

	D3DXMatrixRotationY(&TmpRot, D3DXToRadian(ThrowingInitValue->YAxisAng));		//”­ŽËŒ³‚ÌŠp“x‚©‚çs—ñì¬
	mat = TmpRot * mat;
}

Decoration_BlueBall::~Decoration_BlueBall()
{
}

void Decoration_BlueBall::Draw()
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
