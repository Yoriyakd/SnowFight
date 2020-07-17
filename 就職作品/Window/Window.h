#pragma once
#include"../main.h"
#include"../SingletonBase.h"
#include<windows.h>

//Window���������s���AWindow�̏���ێ�����N���X
class Window : public SingletonBase<Window>
{
	friend class SingletonBase<Window>;		//SingletonBase�ł̃C���X�^���X���͋���
public:
	const HWND& GetHWND(void);

	const bool IsFullScreen(void);

	// �E�B���h�E�̏�����������A����������true��Ԃ�
	bool InitWindow(const HINSTANCE& _hInst, const int _nCmdshow);

	// ���b�Z�[�W���Ǘ�����
	static LRESULT APIENTRY WndFunc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

private:
	//�O���ŃC���X�^���X���֎~
	Window(void);
	~Window(void);

	// �E�B���h�E�n���h��
	HWND hwnd = nullptr;

	// �t���X�N���[�����[�h���ǂ����̃t���O
	bool isFullScreen = false;
};