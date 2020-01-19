#pragma once
#include"../ResourceManager.h"

//------------------------------------------------------------------------
//Player��HIT�����Ƃ��ɕ\������G�t�F�N�g�̃N���X
//Initialize���\�b�h���Ă�ŏ��������Ă���g��
//------------------------------------------------------------------------

//�ǂ̕������炠���������ɕ\��������̂���\��
enum HitEffectID
{
	Right,
	Left,
	Back
};

class PlayerHitEffect{
public:
	PlayerHitEffect();
	~PlayerHitEffect();
	void Initialize_BackEffect();
	void Initialize_RightEffect();
	void Initialize_LeftEffect();
	//�\���������Ԃɂ���
	void Active();
	//���\������Ă��邩�̏�Ԃ��擾����
	bool GetActiveState();

	void Draw();
	void Update();
	//Player���ǂ̕���������ł�����ʂɓ����������v�Z���郁�\�b�h
	static HitEffectID CalculateHitDirection(const D3DXVECTOR3 &SnowBallVec);
private:
	//�\��������W�����߂�ۂɌĂԌĂԂ�ID�Ō��߂�ꂽ�͈͂Ń����_���ȍ��W���Z�b�g�����
	void InitPos();

	LPDIRECT3DTEXTURE9 tex;
	RECT rect;
	D3DXMATRIX transMat;
	D3DXVECTOR3 pos;
	HitEffectID id;
	int alpha;
	static const int DISPLAY_TIME = 60;		//�������Ȃ�����(�t���[���P��)
	int displayCnt;
	bool activeFlag;
};