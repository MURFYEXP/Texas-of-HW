//
//  winpro.cpp
//  Texas_and_fuck
//
//  Created by mac on 5/28/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

#include <cstdlib> // “˝»ÎÕ∑Œƒº˛
#include <ctime> // “˝»Î ±º‰Õ∑Œƒº˛£¨“ª∞„”√¿¥≥ı ºªØÀÊº¥∫Ø ˝±£÷§√ø¥Œ”–∏ˆ≤ªÕ¨µƒÀÊº¥–Ú¡–
#include <iostream>
#include "pokersort.h"
int pokernumber[] = {
	98306, 163843, 294917, 557063, 1081355, 2129933, 4227089, 8421395, 16810007, 33587229, 67141663, 134250533, 268468265,
	81922, 147459, 278533, 540679, 1064971, 2113549, 4210705, 8405011, 16793623, 33570845, 67125279, 134234149, 268451881,
	73730, 139267, 270341, 532487, 1056779, 2105357, 4202513, 8396819, 16785431, 33562653, 67117087, 134225957, 268443689,
	69634, 135171, 266245, 528391, 1052683, 2101261, 4198417, 8392723, 16781335, 33558557, 67112991, 134221861, 268439593,
};//“˝”√≈∆∏Ò Ω◊™ªª ˝◊È£¨
using namespace std;
/*winpro∫Ø ˝Õ®π˝ ÷≈∆∫Õ√˜≈∆º∆À„ªÒ §µƒ∏≈¬ £¨∑µªÿ÷µŒ™ªÒ §∏≈¬ */
double winpro(int myhand[2], int poker[],int pokern, int playn)
{
	/*myhand¥Ê¥¢ ÷≈∆µƒ÷µ£¨poker¥Ê¥¢√˜≈∆µƒ÷µ£¨pokern¥Ê¥¢√˜≈∆µƒ ˝¡ø£¨playn¥Ê¥¢ƒø«∞ÕÊº“µƒ ˝¡ø*/
	//¥Ê¥¢µƒ∑Ω ΩŒ™Ω´52’≈≈∆“¿¥Œ¡–Œ™0µΩ51 ˝◊÷£¨∞¥’’∫⁄Ã“£¨√∑ª®£¨∑Ω∆¨£¨∫ÏÃ“≈≈¡–£¨
	//¿˝»Á13¥˙±Ì√∑ª®2£¨25¥˙±Ì√∑ª®A
	int exit[52];// ˝◊È£¨”√¿¥≈–∂œƒ≥’≈≈∆ «∑Ò“—æ≠≥ˆœ÷
	int winnum = 0;//≥ı ºªØªÒ §¥Œ ˝Œ™0£ª
    
	int temp;
	int allpoker[7];//¥Ê¥¢“ª◊È∆ﬂ’≈≈∆°£
	for (int i = 0; i < pokern; i++)
	{
		allpoker[i] = pokernumber[poker[i]];
	}//Ω´≤ªø…∏¸∏ƒµƒpokern∏ˆ÷µ¥Ê»Î«∞Œª£¨
    
	//allpoker[5] = pokernumber[myhand[0]];
	//allpoker[6] = pokernumber[myhand[1]];
	int mysort;//º∆À„◊‘º∫ ÷≈∆µƒ≈≈√˚
    
	for (int i = 0; i < 1000; i++)//—≠ª∑1000¥Œ£¨’“≥ˆªÒ §¥Œ ˝
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
		}//“—÷™µƒ ÷≈∆∏≥÷µŒ™1
        
		srand((unsigned int)(time(0)*i)); // seedƒ„µƒÀÊº¥∫Ø ˝£¨’‚—˘√ø¥Œ–Ú¡–≤ªÕ¨£¨“ª∞„∏¯µ±«∞ ±º‰◊˜Œ™Ã· æ°£
        
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
            
			if (mysort > compare7(allpoker))//¥˙±Ì◊‘º∫µƒ≈∆±»∆‰À˚»Àªµ
				break;
		}//Œ™µ⁄j∏ˆ≈∆ ÷ÀÊª˙“ª ÷≈∆£¨»Ù∏√≈∆‘⁄÷Æ«∞≥ˆœ÷π˝£¨‘Ú÷ÿ–¬ÀÊª˙°£
		if (j == playn)
			winnum += 1;
	}
	return (double(winnum) / 1000.0);
}

