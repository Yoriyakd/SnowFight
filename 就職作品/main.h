#pragma once
#include<d3dx9.h>

#define GAME_FPS 60		//ここら辺の定数データとかをまとめた情報管理クラスとか作ったほうがいいんだろうか

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height


#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


// 頂点フォーマットの定義
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};


//Xファイルの定義
struct XFILE {
	LPD3DXMESH lpMesh;			//meshの形状データ	
	DWORD NumMaterial;			//グループの数
	D3DMATERIAL9 *Mat;			//マテリアルの内容　* グループ数分
	LPDIRECT3DTEXTURE9 *Tex;	//Textureの内容 * グループ数分		
};

//メッシュの形式簡易化の定義
struct CLONEVERTEX
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 Tex;
};

//飛ばした雪玉に付与
enum ID{PLAYER_ID, ENEMY_ID};

//何かを発射するときに渡すデータの構造体
struct ThrowingInitValue {
	D3DXVECTOR3 shootPos;		//打ち出す位置
	float XAxisAng;				//X軸の回転角度	*Degreeで渡す
	float YAxisAng;				//Y軸の回転角度	*Degreeで渡す
	float powerRate;			//打ち出すパワーの割合	*0~100
};

//当たり判定の球の情報を渡す時に使う構造体
struct CollisionSphere {
	D3DXVECTOR3 pos;
	float radius;
};

//ステージの境界構造体
struct StageBorder
{
	float Top;
	float Bottom;
	float Left;
	float Right;
};

enum CollisionDetectionType{Ray, Circles};

void DrawMesh(XFILE *XFile);

//球同士の当たり判定
bool SphereCollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB);

//メッシュに対してのレイ判定(MeshDisとPolyNoはnullptr許容)		HITしなかった場合MeshDisには-1が入る
bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis, DWORD *PolyNo);

//ThrowingInitValueを渡すと移動ベクトルが返ってきて発射位置の行列作成ができる
D3DXVECTOR3 ThrowingInit(const ThrowingInitValue* ThrowingInitValue, D3DXMATRIX *Mat);

//クオータニオンでアニメーションする関数	第一引数に加工した行列が入る
void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame);

//視点行列を渡してビルボード行列を作成
void MakeBillBoardMat(D3DXMATRIX *OutMat, const D3DXMATRIX *_mView);

//引数で渡された百分率の値が今回trueになるかを返す
bool IsOverProbabilityValue(const int& Probability);