#include "Stage.h"

Ground* ground;


//===============================================
//private
//===============================================

void Stage::SetStageMap(void)
{
	char FileName[16];
	//=================================================================================
	//ファイルオープン
	//=================================================================================

	sprintf_s(FileName, sizeof(FileName), "Map/stage%d.txt", nowStageNo);		//ファイルパス作成

	fopen_s(&fp, FileName, "r");	//fopenのセキュリティ強化版らしい
				

	//=================================================================================
	//読み取った値をセット
	//=================================================================================
	
	//fopenの失敗とかファイルの書き方間違えを検知できない良くない

	int dataBuff[256];
	int i = 0;

	while (dataBuff[i] == EOF)
	{ 
		 ctoi(fgetc(fp));		//結果が0～9じゃなかったら飛ばして次に行く処理を書く
		dataBuff[i];
	}

	//int a;
	//fscanf(fp, "壁:%d\n", &a);		//シーク位置は読んだあと移動する
	//fscanf(fp, "%d ", &a);

//	int b[10] = {0,1,2,3,4,5};
//	fwrite(b, sizeof(b), 1, fp);		バイナリ型式でする必要がある
//	fread(b, sizeof(b), 1, fp);			バイナリ型式で

	//while (1)
	//{
	//	int buf;
	//	
	//	buf = fgetc(fp);			//fscanf_sのほうがいいらしい
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//数字以外はじく
	//	{
	//		enemyNum = buf - '0';			//文字コードを数字に変換
	//		break;
	//	}


	//}

	//while (1)
	//{
	//	int buf;

	//	buf = fgetc(fp);
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//数字以外はじく
	//	{
	//		wallNum = buf - '0';			//文字コードを数字に変換
	//		break;
	//	}


	//}

	//while (1)
	//{
	//	int buf;

	//	buf = fgetc(fp);
	//	if (buf == EOF)break;
	//	if (buf >= '0' && buf <= '9')		//数字以外はじく
	//	{
	//		for (int i = 0; i < stageY; i++)
	//		{
	//			for (int j = 0; j < stageX; j++)	//これじゃダメ全部に同じのが入る　一回いれたら抜けないと
	//			{
	//				StageMap[j][i] = buf - '0';			//文字コードを数字に変換   
	//			}
	//		}
	//		
	//	}


	//}
}

int Stage::ctoi(char c)
{

	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	return -999;

	
}


//===============================================
//public
//===============================================



Stage::Stage(int stageNo)
{
	nowStageNo = stageNo;
	SetStageMap();
	ground = new Ground;			//画像の読み込みがおもい
	enemy.push_back(new Enemy);
}

Stage::~Stage()
{
	fclose(fp);
}

void Stage::Draw()
{
	ground->Draw();
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->Draw();
	}
}
