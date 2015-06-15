//
//  global.h
//  各种测试用
//
//  Created by mac on 5/25/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

#ifndef ______global_h
#define ______global_h

extern char card_flop0[20];
extern char card_flop1[20];
extern char card_flop2[20];
extern char card_hold0[20];
extern char card_hold1[20];
//extern char Action[20];
extern char Pot[20];
extern char turn_card[20];
extern char river_card[20];
extern char temp[7][12];
extern int foldedNum;
extern int is_inquired;

/*如需跟注数*/
extern char callNum[10];
/*明牌*/
extern char a[5][12];
/*明牌数*/
extern int n;

#endif
