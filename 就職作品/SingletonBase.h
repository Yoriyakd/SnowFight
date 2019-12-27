#pragma once
//----------------------------------------------------------------
//シングルトンクラスの基底クラス
//継承して使う
//----------------------------------------------------------------

template<class T>

class SingletonBase
{
public:
	//インスタンスを返す
	static inline T& GetInstance()
	{
		return *instance;
	}

	static inline void Create()			//インスタンス作成
	{
		if (instance == nullptr)
		{
			instance = new T;
		}
	};
	static inline void Destroy()			//インスタンス削除
	{
		delete instance;
		instance = nullptr;
	};

protected:
	SingletonBase() {};										//外部でのインスタンス作成禁止

	virtual ~SingletonBase() {};
private:
	void operator=(const SingletonBase& obj) {};			//演算子をオーバーロードして代入を禁止している(アップキャストだと入れられる)
	SingletonBase(const SingletonBase &obj) {};				//コピーコンストラクタを禁止してインスタンスが別のオブジェクトで初期化されるのを防ぐ

	static T *instance;
};