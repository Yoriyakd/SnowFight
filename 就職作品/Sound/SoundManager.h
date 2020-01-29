#pragma once
#include"../SingletonBase.h"
#include"Sound2D.h"
#include"Sound3D.h"
#include<map>


#define GetSound SoundManager::GetInstance()
class SoundManager : public SingletonBase<SoundManager>{
	friend class SingletonBase<SoundManager>;
public:
	SoundManager();
	~SoundManager();

	//���s��false���Ԃ�
	bool Play2D(SoundID);

	void AllStop();

	void Initialize();
	void Update();
	
private:
	std::map<SoundID, Sound2D*> Sound2DMap;			//2D�T�E���h�Ǘ�(3D�������ɓ��ꂽ�����������W���̐ݒ���@���v�����Ȃ�����)
	std::map<SoundID, Sound3D*> Sound3DMap;			//3D�T�E���h�Ǘ�

	void AllDelete();
};

SoundManager* SingletonBase<SoundManager>::instance = nullptr;