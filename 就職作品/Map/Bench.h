#pragma once
#include"MapObj.h"
#include"../ResourceManager.h"
class Bench : public MapObj
{
public:
	Bench(D3DXVECTOR3 Pos, float Ang);		//�u�����W��]��n��
	~Bench();
	XFILE GetMesh();			//�����蔻��p�̃��b�V����Ԃ��@�I�[�o�[���C�h���Ă���
private:
	XFILE collisionMesh;		//�����蔻��p�̃��b�V��
};
