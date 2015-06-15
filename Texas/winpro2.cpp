#include <cstdlib> // ����ͷ�ļ�
#include <ctime> // ����ʱ��ͷ�ļ���һ��������ʼ���漴������֤ÿ���и���ͬ���漴����
#include <iostream>
#include "pokersort.h"
int pokernumber[] = {
	98306, 163843, 294917, 557063, 1081355, 2129933, 4227089, 8421395, 16810007, 33587229, 67141663, 134250533, 268468265,
	81922, 147459, 278533, 540679, 1064971, 2113549, 4210705, 8405011, 16793623, 33570845, 67125279, 134234149, 268451881,
	73730, 139267, 270341, 532487, 1056779, 2105357, 4202513, 8396819, 16785431, 33562653, 67117087, 134225957, 268443689,
	69634, 135171, 266245, 528391, 1052683, 2101261, 4198417, 8392723, 16781335, 33558557, 67112991, 134221861, 268439593,
};//�����Ƹ�ʽת�����飬
using namespace std;
/*winpro����ͨ�����ƺ����Ƽ����ʤ�ĸ��ʣ�����ֵΪ��ʤ����*/
double winpro(int myhand[2], int poker[],int pokern, int playn)
{
	/*myhand�洢���Ƶ�ֵ��poker�洢���Ƶ�ֵ��pokern�洢���Ƶ�������playn�洢Ŀǰ��ҵ�����*/
	//�洢�ķ�ʽΪ��52����������Ϊ0��51���֣����պ��ң�÷������Ƭ���������У�
	//����13����÷��2��25����÷��A
	int exit[52];//���飬�����ж�ĳ�����Ƿ��Ѿ�����
	int winnum = 0;//��ʼ����ʤ����Ϊ0��

	int temp;
	int allpoker[7];//�洢һ�������ơ�
	for (int i = 0; i < pokern; i++)
	{
		allpoker[i] = pokernumber[poker[i]];
	}//�����ɸ��ĵ�pokern��ֵ����ǰλ��

	//allpoker[5] = pokernumber[myhand[0]];
	//allpoker[6] = pokernumber[myhand[1]];
	int mysort;//�����Լ����Ƶ�����

	for (int i = 0; i < 1000; i++)//ѭ��1000�Σ��ҳ���ʤ����
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
		}//��֪�����Ƹ�ֵΪ1

		srand((unsigned int)(time(0)*i)); // seed����漴����������ÿ�����в�ͬ��һ�����ǰʱ����Ϊ��ʾ��

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

			if (mysort > compare7(allpoker))//�����Լ����Ʊ������˻�
				break;
		}//Ϊ��j���������һ���ƣ���������֮ǰ���ֹ��������������
		if (j == playn)
			winnum += 1;
	}
	return (double(winnum) / 1000.0);
}