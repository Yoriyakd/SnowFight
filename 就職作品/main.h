#pragma once
#include<d3dx9.h>


extern LPDIRECT3D9				lpD3D;		// Direct3Dインターフェイス
extern LPDIRECT3DDEVICE9		lpD3DDevice;	// Direct3DDeviceインターフェイス
extern LPD3DXSPRITE lpSprite;	// スプライト
extern LPD3DXFONT lpFont;		// フォント
extern D3DPRESENT_PARAMETERS d3dpp;
extern HWND hwnd;
extern const int GameFPS;

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

//雪玉を発射するときに渡すデータの構造体
struct SnowBallInitValue {
	D3DXVECTOR3 shootPos;		//打ち出す位置
	float XAxisAng;				//X軸の回転角度	*Degreeで渡す
	float YAxisAng;				//Y軸の回転角度	*Degreeで渡す
	float powerRate;			//打ち出すパワーの割合	*0~100
	ID id;						//発射したキャラをenumで定義したIDを入れる
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

//ボールデコレーションの色		//main.cppで値を初期化
struct Decoration_BallColor
{
	D3DCOLORVALUE RED_BALL_COLOR;
	D3DCOLORVALUE BLUE_BALL_COLOR;
	D3DCOLORVALUE GREEN_BALL_COLOR;
};

extern Decoration_BallColor decoration_BallColor;		//main.cppで宣言

enum CollisionDetectionType{Ray, Circles};

void DrawMesh(XFILE *XFile);
void DrawMesh(XFILE *XFile, D3DCOLORVALUE Color);

//球同士の当たり判定
bool CollisionDetection(CollisionSphere *dataA, CollisionSphere *dataB);

//メッシュに対してのレイ判定
bool MeshCollisionDetection(XFILE *Mesh, D3DXMATRIX *MeshMat, D3DXVECTOR3 *LayPos, D3DXVECTOR3 *LayVec, float *MeshDis);

//SnowBallInitValueを渡すと移動ベクトルが返ってきて発射位置の行列作成ができる
D3DXVECTOR3 SnowBallInit(SnowBallInitValue* SnowBallInitValue, D3DXMATRIX *Mat);

//クオータニオンでアニメーションする関数	第一引数に加工した行列が入る
void QuaternionAnime(D3DXMATRIX *OutMat, const D3DXMATRIX *NowMat, const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float AnimeFrame);