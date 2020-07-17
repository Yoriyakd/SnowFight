#include "DirectSound.h"
#include"../Window/Window.h"

bool DirectSound::InitDirectSound(void)
{
	if (lpDSound != nullptr)
	{
		return true;		//既に存在するなら抜ける
	}

	DirectSoundCreate8(NULL, &lpDSound, NULL);

	//協調レベルを設定
	lpDSound->SetCooperativeLevel(Window::GetInstance().GetHWND(), DSSCL_PRIORITY);

	// プライマリ・バッファの作成
	// DSBUFFERDESC構造体を設定
	DSBUFFERDESC dsbdesc;
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	// プライマリ・バッファを指定
	dsbdesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat = NULL;

	// バッファを作る
	lpDSound->CreateSoundBuffer(&dsbdesc, &lpSPrimary, NULL);

	// プライマリ・バッファのWaveフォーマットを設定
	// 　　　優先協調レベル以上の協調レベルが設定されている必要があります．
	WAVEFORMATEX pcmwf;
	ZeroMemory(&pcmwf, sizeof(WAVEFORMATEX));
	pcmwf.wFormatTag = WAVE_FORMAT_PCM;
	pcmwf.nChannels = 2;		// ２チャンネル（ステレオ）
	pcmwf.nSamplesPerSec = 44100;	// サンプリング・レート　44.1kHz
	pcmwf.nBlockAlign = 4;
	pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
	pcmwf.wBitsPerSample = 16;		// 16ビット
	lpSPrimary->SetFormat(&pcmwf);

	CoInitialize(NULL);

	return true;
}

const LPDIRECTSOUND8& DirectSound::GetLpDSound(void)
{
	return lpDSound;
}

DirectSound::DirectSound()
{
}

DirectSound::~DirectSound()
{
	lpSPrimary->Release();		//lpSPrimaryを先に開放する
	lpDSound->Release();
	CoUninitialize();
}
