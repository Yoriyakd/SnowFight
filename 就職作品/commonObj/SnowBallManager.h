#pragma once
#include"../main.h"
#include<vector>
#include"SnowBall.h"
#include"../Effect/EffectManager.h"
#include"../SingletonBase.h"
//------------------------------------------------------------------------
//��ʂ̃C���X�^���X�����N���X
//���V���O���g���N���X
//------------------------------------------------------------------------

#define GetSnowBallManager SnowBallManager::GetInstance()

class SnowBallManager : public SingletonBase<SnowBallManager>{
	friend class SingletonBase<SnowBallManager>;			//SingletonBase�ł̃C���X�^���X�쐬�폜�͋���
public:
	std::vector <SnowBall*> snowBall;	
	//�S�C���X�^���X�폜
	void AllDelete(void);
	//���������C���X�^���X�̔z��ԍ���n���Ƃ��̃C���X�^���X���폜����
	void DeleteInstance(unsigned int ite);
	//��������snowBallInitValue�^���|�C���^�œn��
	void SetSnowBall(ThrowingInitValue *ThrowingInitValue, ID _ID);
	void Draw(void);
	void Update(void);
private:
	SnowBallManager();
	~SnowBallManager();
};