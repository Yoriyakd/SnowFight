#include"ArmRAnimeFront.h"
#include"ArmRAnimeMid.h"
const float ArmRAnimeFront::AnimeSpeed = 0.05f;

ArmRAnimeFront::ArmRAnimeFront(D3DXMATRIX *StartMat)
{
	startMat = *StartMat;
	animeFrame = 0.0f;
	D3DXMATRIX EndRotTmp, EndTransTmp;

	D3DXMatrixRotationX(&EndRotTmp, D3DXToRadian(-30));
	D3DXMatrixTranslation(&EndTransTmp, 1.5f, -2.5f, 5.5f);		//カメラからの距離

	endMat = EndRotTmp * EndTransTmp;		//前振りの終端
}

ArmRAnimeFront::~ArmRAnimeFront()
{
}

ArmRAnimeBase* ArmRAnimeFront::Anime(D3DXMATRIX *NowMat)
{
	animeFrame += AnimeSpeed;

	D3DXQUATERNION StartQua, NowQua, EndQua;

	//行列をクオータニオンに変換

	D3DXQuaternionRotationMatrix(&NowQua, NowMat);
	D3DXQuaternionRotationMatrix(&StartQua, &startMat);
	D3DXQuaternionRotationMatrix(&EndQua, &endMat);

	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, animeFrame);

	D3DXMatrixRotationQuaternion(NowMat, &NowQua);

	D3DXVECTOR3 StartPos, NowPos, EndPos;

	StartPos = D3DXVECTOR3(startMat._41, startMat._42, startMat._43);
	EndPos = D3DXVECTOR3(endMat._41, endMat._42, endMat._43);

	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, animeFrame);

	NowMat->_41 = NowPos.x;
	NowMat->_42 = NowPos.y;
	NowMat->_43 = NowPos.z;

	if (animeFrame >= 1)
	{
		return new ArmRAnimeMid(&endMat);
	}
	return nullptr;
}
