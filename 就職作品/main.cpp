#include<time.h>
#include<windows.h>
#include<stdio.h>
#include"main.h"
#include"SceanSwitcher/SceneSwitcher.h"
#include"GameScene/GameScene.h"
#include"TitleScene/TitleScene.h"
#include"ResourceManager.h"
#include"Effect/EffectManager.h"


#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")



LPDIRECT3D9				lpD3D;		// Direct3D�C���^�[�t�F�C�X

LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDevice�C���^�[�t�F�C�X

D3DPRESENT_PARAMETERS d3dpp;


////  �O���[�o���ϐ��錾

LPD3DXSPRITE lpSprite;	// �X�v���C�g
LPD3DXFONT lpFont;		// �t�H���g

bool gameFullScreen;	// �t���X�N���[���itrue,false)
HWND hwnd;
const int GameFPS = 60;		//�Q�[����FPS�w��

SceneSwitcher sceneSwitcher;
ResourceManager *resourceManager;
EffectManager *effectManager;

void DrawMesh(XFILE *XFile)
{
	for (DWORD i = 0; i < XFile->NumMaterial; i++)
	{
		lpD3DDevice->SetMaterial(&(XFile->Mat[i]));
		lpD3DDevice->SetTexture(0, XFile->Tex[i]);
		XFile->lpMesh->DrawSubset(i);
	}
}

void DrawMesh(XFILE *XFile, D3DCOLORVALUE Color)
{
	for (DWORD i = 0; i < XFile->NumMaterial; i++)
	{
		//XFILE  TmpXFILE;
		D3DMATERIAL9 TmpMat;
		TmpMat = *XFile->Mat;
		TmpMat.Emissive = Color;

		lpD3DDevice->SetMaterial(&(TmpMat));
		lpD3DDevice->SetTexture(0, XFile->Tex[i]);
		XFile->lpMesh->DrawSubset(i);
	}
}

//���W�A���a�A���W�A���a
//�߂�l�@HIT == true �������ĂȂ������� == falsle
bool CollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB)
{
	float targetLengh;
	targetLengh = D3DXVec3Length(&(dataA->pos - dataB->pos));
	if (targetLengh <= dataA->radius + dataB->radius)
	{
		return true;
	}
	return false;
}

bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis)
{
	D3DXMATRIX InvMat;
	D3DXMatrixInverse(&InvMat, NULL, &*MeshMat);

	D3DXVECTOR3 LocalPos, LocalVec;

	D3DXVec3TransformCoord(&LocalPos, &*LayPos, &InvMat);		//���C���ˈʒu
	D3DXVec3TransformNormal(&LocalVec, &*LayVec, &InvMat);			//���C���˕���

	BOOL Hit;
	
	D3DXIntersect(Mesh->lpMesh, &LocalPos, &LocalVec, &Hit, NULL, NULL, NULL, &*MeshDis, NULL, NULL);
	if (Hit == FALSE)
	{
		*MeshDis = -1;
		return false;
	}
	return true;
}

D3DXVECTOR3 SnowBallInit(SnowBallInitValue* snowBallInitValue, D3DXMATRIX *Mat)
{
	float Power;
	D3DXVECTOR3 moveVec;
	Power = ((snowBallInitValue->powerRate / 100)) * 3;		//�򋗗������̂��߂�3

	D3DXMatrixTranslation(Mat, snowBallInitValue->shootPos.x, snowBallInitValue->shootPos.y, snowBallInitValue->shootPos.z);			//���ˈʒu

	moveVec = D3DXVECTOR3(0, (Power * tan(D3DXToRadian(snowBallInitValue->XAxisAng))), (Power * cos(D3DXToRadian(snowBallInitValue->XAxisAng))));	//���˂̃x�N�g�������߂�

	return moveVec;
}

void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame)
{
	D3DXQUATERNION StartQua, NowQua, EndQua;

	//�s����N�I�[�^�j�I���ɕϊ�

	D3DXQuaternionRotationMatrix(&NowQua, NowMat);
	D3DXQuaternionRotationMatrix(&StartQua, StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, EndMat);

	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, AnimeFrame);

	D3DXMatrixRotationQuaternion(OutMat, &NowQua);

	D3DXVECTOR3 StartPos, NowPos, EndPos;

	StartPos = D3DXVECTOR3(StartMat->_41, StartMat->_42, StartMat->_43);
	EndPos = D3DXVECTOR3(EndMat->_41, EndMat->_42, EndMat->_43);

	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);

	OutMat->_41 = NowPos.x;
	OutMat->_42 = NowPos.y;
	OutMat->_43 = NowPos.z;
}

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


LRESULT APIENTRY WndFunc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
		}
		return 0;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);

}



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPSTR lpszCmdParam, int nCmdshow)
{
	MSG msg;

	//HWND hwnd;
	WNDCLASS wc;
	char szAppName[] = "Generic Game SDK Window";

	wc.style = CS_DBLCLKS;
	wc.lpfnWndProc = WndFunc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(
		0,
		szAppName,
		"SnowBallFight",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCRW, SCRH,
		NULL, NULL, hInst,
		NULL);

	if (!hwnd)return FALSE;

	ShowWindow(hwnd, nCmdshow);
	UpdateWindow(hwnd);
	SetFocus(hwnd);

	gameFullScreen = false;	// �E�B���h�E���[�h
	if (MessageBox(NULL, "�t���X�N���[���ŋN�����܂���?", "�N���m�F", MB_YESNO | MB_DEFBUTTON2 | MB_ICONQUESTION) == IDYES)
	{
		gameFullScreen = true;
	}
	if (gameFullScreen) {
		ShowCursor(FALSE);
	}
	else {
		RECT rc = { 0,0,SCRW,SCRH };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(hwnd, NULL, 50, 50, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW | SWP_NOZORDER);
	}

	//---------------------DirectX Graphics�֘A-----------------------

	// Direct3D �I�u�W�F�N�g���쐬
	lpD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL, "Direct3D �̍쐬�Ɏ��s���܂����B", "ERROR", MB_OK | MB_ICONSTOP);
		// �I������
		return 0;
	}
	int adapter;

	// �g�p����A�_�v�^�ԍ�
	adapter = D3DADAPTER_DEFAULT;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	// Direct3D �������p�����[�^�̐ݒ�
	if (gameFullScreen)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		D3DDISPLAYMODE disp;
		// ���݂̉�ʃ��[�h���擾
		lpD3D->GetAdapterDisplayMode(adapter, &disp);
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = SCRW;
	d3dpp.BackBufferHeight = SCRH;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;

	if (!gameFullScreen)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}

	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�ޯ��ޯ̧��ۯ��\�ɂ���(GetDC���\�ɂȂ�)
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	//FPS��������
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(lpD3D->CreateDevice(adapter, D3DDEVTYPE_REF, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &lpD3DDevice)))
			{
				// ���ǎ��s����
				MessageBox(NULL, "DirectX9���������ł��܂���B\n���Ή��̃p�\�R���Ǝv���܂��B", "ERROR", MB_OK | MB_ICONSTOP);
				lpD3D->Release();
				// �I������
				return 0;
			}
		}
	}

	// �����_�����O�E�X�e�[�g��ݒ�
	// Z �o�b�t�@�L����->�O��֌W�̌v�Z�𐳊m�ɂ��Ă����
	lpD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�u�����f�B���O�L����
	lpD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	// �A���t�@�u�����f�B���O���@��ݒ�
	lpD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �����_�����O���̃A���t�@�l�̌v�Z���@�̐ݒ�
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	// �e�N�X�`���̐F���g�p
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	// ���_�̐F���g�p
	lpD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	// �����_�����O���̐F�̌v�Z���@�̐ݒ�
	lpD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//���ʃJ�����O
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �t�B���^�ݒ�
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	lpD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// ���C�g
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	lpD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	// ���_�t�H�[�}�b�g�̐ݒ�
	lpD3DDevice->SetFVF(FVF_VERTEX);

	timeBeginPeriod(1);

	// �Q�[���Ɋւ��鏉�������� ---------------------------
	resourceManager = new ResourceManager();
	effectManager = new EffectManager();




	// �X�v���C�g�쐬
	D3DXCreateSprite(lpD3DDevice, &lpSprite);
	lpSprite->OnResetDevice();

	// �t�H���g�쐬
	D3DXCreateFont(lpD3DDevice, 30, 30, FW_REGULAR, NULL, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, "�l�r �S�V�b�N", &lpFont);

	lpFont->OnResetDevice();

	sceneSwitcher.SwitchScene(new TitleScene());

	
	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			sceneSwitcher.NowScene();
		}
	}

	// �Q�[���Ɋւ���I������ ---------------------------
	delete resourceManager;
	delete effectManager;


	lpSprite->Release();	// �X�v���C�g
	lpFont->Release();		// �t�H���g


	timeEndPeriod(1);

	// Direct3D �I�u�W�F�N�g�����
	lpD3DDevice->Release();
	lpD3D->Release();

	return (int)msg.wParam;
}