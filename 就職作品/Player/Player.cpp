#include "Player.h"

extern ResourceManager *resourceManager;
//=====================================
//privateメソッド
//=====================================

void Player::Move(void)
{
	///*--ここで毎回リセットしている--*/
	//bool moveFlag = false;
	//D3DXVECTOR3 moveVec(0, 0, 0);
	///*--ここで毎回リセットしている--*/
	//D3DXVECTOR3 TmpVec;


	//if (GetAsyncKeyState('W') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, 1), &camRotMatX);
	//	/*ここを切り替えて他のキーを作る*/
	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('A') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(-1, 0, 0), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('S') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(0, 0, -1), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}
	//if (GetAsyncKeyState('D') & 0x8000)
	//{
	//	D3DXVec3TransformNormal(&TmpVec, &D3DXVECTOR3(1, 0, 0), &camRotMatX);

	//	moveVec += TmpVec;
	//	moveFlag = true;
	//}

	////押してる間だけ動く
	//if (moveFlag == true)
	//{
	//	D3DXVec3Normalize(&moveVec, &moveVec);

	//	D3DXMATRIX tmpMat;
	//	D3DXMatrixTranslation(&tmpMat,
	//		moveVec.x,
	//		moveVec.y,
	//		moveVec.z);

	//	D3DXVECTOR3 nowVec;
	//	D3DXVec3TransformNormal(&nowVec, &D3DXVECTOR3(0, 0, 1), &rotMat);			//今向いている方向のベクトルを入れている		//確か長さを1にしている斜め移動が速くなるやつの対策
	//	D3DXVec3Normalize(&moveVec, &moveVec);
	//	float tmpAng;
	//	tmpAng = D3DXVec3Dot(&nowVec, &moveVec);
	//	tmpAng = D3DXToDegree(acos(tmpAng));

	//	if (tmpAng >= 0.1f)			//float型では== や!=　を使わない
	//	{
	//		D3DXVECTOR3 crossVec;
	//		D3DXVec3Cross(&crossVec, &nowVec, &moveVec);			//外積を計算してベクトルが上か下かを見る

	//		if (tmpAng >= 10.0f)			//ゆっくりかいてんさせる処理
	//		{
	//			tmpAng = 8.0f;
	//		}

	//		if (crossVec.y > 0.1f)			//ここの桁数を増やすと振動がなくなるっぽい
	//		{
	//			camAngY += tmpAng;
	//		}
	//		else
	//		{
	//			if (crossVec.y < -0.1f)		//ここの桁数を増やすと振動がなくなるっぽい
	//			{
	//				camAngY -= tmpAng;
	//			}
	//			else
	//			{
	//				camAngY += tmpAng;			//180度開いているようなときは(どちらにも当てはまらない)
	//			}
	//		}
	//	}

	//	D3DXMatrixRotationY(&rotMat, D3DXToRadian(camAngY));

	//	transMat = tmpMat * transMat;
	//}

	//mat = rotMat * transMat;
}

int Player::ShootSnowball(void)
{
	return 0;
}

//=====================================
//publicメソッド
//=====================================

Player::Player()
{
	mesh = resourceManager->GetXFILE("Player/player.x");
	SetCursorPos(SCRW / 2, SCRH / 2);
	camAngX = 0, camAngY = 0;
	basePt.x = SCRH / 2;
	basePt.y = SCRW / 2;

	ClientToScreen(hwnd, &basePt);
	SetCursorPos(basePt.x, basePt.y);
}

Player::~Player()
{

}

bool Player::Update(void)
{
	Move();
	D3DXMatrixTranslation(&mat, 0, 0, 0);		//仮
	Pos.x = mat._41, Pos.y = mat._42 + 5, Pos.z = mat._43;		//Playerの座標をPosに入れる		場所考え中
	return true;
}

void Player::SetCamera(void)
{
	D3DXMATRIX mView, mProj;

	/*if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		AngY++;
	}*/

	

	POINT Pt;					
	GetCursorPos(&Pt);					//現在のカーソルの位置をいれる
	camAngY += (Pt.x - basePt.x) / 4.0f;	//最初の位置との差を求め、移動量を調整している
	
	camAngX += (Pt.y - basePt.y) / 4.0f;
	SetCursorPos(basePt.x, basePt.y);	//カーソル位置リセット		スクリーン座標に変換したほうがいい気がする

	if (camAngX >= 70)
	{
		camAngX = 70;
	}
	
	if (camAngX <= -70)
	{
		camAngX = -70;
	}

	D3DXMatrixRotationY(&camRotMatY, D3DXToRadian(camAngY));				//傾いた分だけ回転させる
	
	D3DXMatrixRotationX(&camRotMatX, D3DXToRadian(camAngX));				//傾いた分だけ回転させる

	camRotMat = camRotMatX * camRotMatY;

	D3DXVECTOR3 camTmpVec;

	D3DXVec3TransformCoord(&camTmpVec, &D3DXVECTOR3(0, 0, 1), &camRotMat);	//最初の向きと傾いた分のベクトルを合わせる

	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		&Pos,	// カメラの位置
		&(Pos + camTmpVec),	// カメラの視点
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);
	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), (float)SCRW / (float)SCRH, 1.0f, 1000.0f);

	//行列設定
	lpD3DDevice->SetTransform(D3DTS_VIEW, &mView);
	lpD3DDevice->SetTransform(D3DTS_PROJECTION, &mProj);
}

void Player::Draw(void)
{
	lpD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	DrawMesh(&mesh);
}
