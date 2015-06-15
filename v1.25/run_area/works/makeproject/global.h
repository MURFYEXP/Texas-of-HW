//
//  global.h
//  Texas_and_fuck
//
//  Created by mac on 5/28/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

//
//  global.h
//  各种测试用
//
//  Created by mac on 5/25/15.
//  Copyright (c) 2015 mac. All rights reserved.
//
extern char card_flop0[20];
extern char card_flop1[20];
extern char card_flop2[20];
extern char card_hold0[20];
extern char card_hold1[20];
extern char Money[10];
extern int money;
extern char Pot[20];
extern char turn_card[20];
extern char river_card[20];
extern char Jetton[20];
extern int jetton;
extern int a[5];
extern int b[2];

extern int is_inquired;
extern int is_holded;
extern int is_floped;
extern int is_turned;
extern int is_rivered;

extern int pre_max;
extern int my_id;
extern int id_len;
extern char str_pid[10];
extern int had_all_in;
extern int had_fold;

extern char callNum[100];
extern int m_socket_id;
extern int foldedNum;
extern int  total_pot;
extern int n;
extern int playn;
extern int thisturn;
extern double power;
extern int my_id;
extern double pot;


int transform2(char *a);
