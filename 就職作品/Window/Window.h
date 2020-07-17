#pragma once
#include"../main.h"
#include"../SingletonBase.h"
#include<windows.h>

//Window初期化を行い、Windowの情報を保持するクラス
class Window : public SingletonBase<Window>
{
	friend class SingletonBase<Window>;		//SingletonBaseでのインスタンス化は許可
public:
	const HWND& GetHWND(void);

	const bool IsFullScreen(void);

	// ウィンドウの初期化をする、成功したらtrueを返す
	bool InitWindow(const HINSTANCE& _hInst, const int _nCmdshow);

	// メッセージを管理する
	static LRESULT APIENTRY WndFunc(HWND _hwnd, UINT _msg, WPARAM _wParam, LPARAM _lParam);

private:
	//外部でインスタンス化禁止
	Window(void);
	~Window(void);

	// ウィンドウハンドル
	HWND hwnd = nullptr;

	// フルスクリーンモードかどうかのフラグ
	bool isFullScreen = false;
};