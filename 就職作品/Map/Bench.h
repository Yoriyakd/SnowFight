#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bench : public MapObj
{
private:
	D3DXVECTOR3 pos;
	XFILE collisionMesh;		//�����蔻��p�̃��b�V��
public:
	Bench(D3DXVECTOR3 Pos);		//�u�����W��n��
	~Bench();
	XFILE GetMesh();			//�����蔻��p�̃��b�V����Ԃ��@�I�[�o�[���C�h���Ă���
};
