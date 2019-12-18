#pragma once
#include"../main.h"
#include<vector>
#include"SnowBall.h"
#include"../Effect/EffectManager.h"
//------------------------------------------------------------------------
//��ʂ̃C���X�^���X�����N���X
//------------------------------------------------------------------------
class SnowBallManager {
private:
public:
	std::vector <SnowBall*> snowBall;
	SnowBallManager();
	~SnowBallManager();
	//�S�C���X�^���X�폜
	void AllDelete(void);
	//���������C���X�^���X�̔z��ԍ���n���Ƃ��̃C���X�^���X���폜����
	void DeleteInstance(unsigned int ite);
	//��������snowBallInitValue�^���|�C���^�œn��
	void SetSnowBall(ThrowingInitValue *ThrowingInitValue, ID _ID);
	void Draw(void);
	void Update(void);
};
