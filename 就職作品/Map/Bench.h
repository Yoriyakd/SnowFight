#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bench : public MapObj
{
public:
	Bench(D3DXVECTOR3 Pos);		//�u�����W��n��
	~Bench();
	XFILE GetMesh();			//�����蔻��p�̃��b�V����Ԃ��@�I�[�o�[���C�h���Ă���

private:
	D3DXVECTOR3 pos;
	XFILE collisionMesh;		//�����蔻��p�̃��b�V��
};
