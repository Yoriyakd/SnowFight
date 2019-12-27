#pragma once
//----------------------------------------------------------------
//�V���O���g���N���X�̊��N���X
//�p�����Ďg��
//----------------------------------------------------------------

template<class T>

class SingletonBase
{
public:
	//�C���X�^���X��Ԃ�
	static inline T& GetInstance()
	{
		return *instance;
	}

	static inline void Create()			//�C���X�^���X�쐬
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
	};
	static inline void Destroy()			//�C���X�^���X�폜
	{
		delete instance;
		instance = nullptr;
	};

protected:
	SingletonBase() {};										//�O���ł̃C���X�^���X�쐬�֎~

	virtual ~SingletonBase() {};
private:
	void operator=(const SingletonBase& obj) {};			//���Z�q���I�[�o�[���[�h���đ�����֎~���Ă���(�A�b�v�L���X�g���Ɠ������)
	SingletonBase(const SingletonBase &obj) {};				//�R�s�[�R���X�g���N�^���֎~���ăC���X�^���X���ʂ̃I�u�W�F�N�g�ŏ����������̂�h��

	static T *instance;
};