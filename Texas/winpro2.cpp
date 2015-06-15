#include <cstdlib> // 引入头文件
#include <ctime> // 引入时间头文件，一般用来初始化随即函数保证每次有个不同的随即序列
#include <iostream>
#include "pokersort.h"
int pokernumber[] = {
	98306, 163843, 294917, 557063, 1081355, 2129933, 4227089, 8421395, 16810007, 33587229, 67141663, 134250533, 268468265,
	81922, 147459, 278533, 540679, 1064971, 2113549, 4210705, 8405011, 16793623, 33570845, 67125279, 134234149, 268451881,
	73730, 139267, 270341, 532487, 1056779, 2105357, 4202513, 8396819, 16785431, 33562653, 67117087, 134225957, 268443689,
	69634, 135171, 266245, 528391, 1052683, 2101261, 4198417, 8392723, 16781335, 33558557, 67112991, 134221861, 268439593,
};//引用牌格式转换数组，
using namespace std;
/*winpro函数通过手牌和明牌计算获胜的概率，返回值为获胜概率*/
double winpro(int myhand[2], int poker[],int pokern, int playn)
{
	/*myhand存储手牌的值，poker存储明牌的值，pokern存储明牌的数量，playn存储目前玩家的数量*/
	//存储的方式为将52张牌依次列为0到51数字，按照黑桃，梅花，方片，红桃排列，
	//例如13代表梅花2，25代表梅花A
	int exit[52];//数组，用来判断某张牌是否已经出现
	int winnum = 0;//初始化获胜次数为0；

	int temp;
	int allpoker[7];//存储一组七张牌。
	for (int i = 0; i < pokern; i++)
	{
		allpoker[i] = pokernumber[poker[i]];
	}//将不可更改的pokern个值存入前位，

	//allpoker[5] = pokernumber[myhand[0]];
	//allpoker[6] = pokernumber[myhand[1]];
	int mysort;//计算自己手牌的排名

	for (int i = 0; i < 1000; i++)//循环1000次，找出获胜次数
	{
		for (int j = 0; j < 52; j++)
		{
			exit[j] = 0;
		}
		exit[myhand[0]] = 1;
		exit[myhand[1]] = 1;

		for (int j = 0; j < pokern; j++)
		{
			exit[poker[j]] = 1;
		}//已知的手牌赋值为1

		srand((unsigned int)(time(0)*i)); // seed你的随即函数，这样每次序列不同，一般给当前时间作为提示。

		int j;
		for (j = pokern; j < 5; j++)
		{
			while (exit[temp = ((int)rand()) % 52] == 1);
			exit[temp] = 1;
			allpoker[j] = pokernumber[temp];
		}
		allpoker[5] = pokernumber[myhand[0]];
		allpoker[6] = pokernumber[myhand[1]];

		mysort = compare7(allpoker);

		for (j = 0; j < playn; j++)
		{
			while (exit[temp = ((int)rand())%52] == 1);
			exit[temp] = 1;
			allpoker[5] = pokernumber[temp];

			while (exit[temp = ((int)rand()) % 52] == 1);
			exit[temp] = 1;
			allpoker[6] = pokernumber[temp];

			if (mysort > compare7(allpoker))//代表自己的牌比其他人坏
				break;
		}//为第j个牌手随机一手牌，若该牌在之前出现过，则重新随机。
		if (j == playn)
			winnum += 1;
	}
	return (double(winnum) / 1000.0);
}