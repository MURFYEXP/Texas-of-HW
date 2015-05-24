//
//  main.c
//  各种测试用
//
//  Created by mac on 2/13/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

/*解析通讯信息v0.1版，目前可解析hold，inquire，flop，turn，river信息。原理：使用strtok函数将缓冲区信息切割成单个的字符串，然后进行筛选匹配；
 由于牌的内容格式均为 color point，所以我们直接在game主函数里面写一个解析花色和点数的函数即可；
 Ps：目前只支持解析以上信息，需要某个信息，再添加即可*/
#include<stdio.h>
#include<string.h>
char *analy_hlod(char *str);
char *analy_inquire(char *str);
char *analy_flop(char *str);
char *analy_turn_And_river(char *str);

/*解析转牌，河牌消息，一个one_hold数组保存一张手牌内容，方便策略函数传参调用*/
char one_card[10] = {'\0'};
char *analy_turn_And_river(char *str)
{
    int i;
    char *ptr;
    char str_river[] = {"\n/river"};
    char str_turn[] = {"\n/turn"};
    /*用“\n”分割buffer信息*/
    char *delim = "\n";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        printf("one_card:");
        for (i = 0; *ptr != '\0'; ++ptr, ++i) {
            one_card[i] = *ptr;
        }
        printf("%s", one_card);
        printf("\n");
        
        /*跳过“\n/river \n”,得到river信息的尾指针*/
        if (strcmp(str_river, ptr)) {
            ptr += 9;
            break;
        }
        /*跳过“\n/turn \n”,得到turn信息的尾指针*/
        if (strcmp(str_turn, ptr)) {
            ptr += 8;
            break;
        }
    }
    return ptr;
}

/*解析公牌消息，一个card_flop数组保存一张手牌内容，方便策略函数传参调用*/
char card_flop0[10] = {'\0'};
char card_flop1[10] = {'\0'};
char card_flop2[10] = {'\0'};
char *analy_flop(char *str)
{
    int i;
    char *ptr;
    char str_flop[] = {"\n/flop"};
    /*用“\n”分割buffer信息*/
    char *delim = "\n";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        printf("card_flop0:");
        for (i = 0; *ptr != '\0'; ++ptr, ++i) {
            card_flop0[i] = *ptr;
            printf("%c", card_flop0[i]);
        }
        printf("\n");
        
        ++ptr;
        printf("card_flop1:");
        for (i = 0; *ptr != '\n'; ++ptr, ++i) {
            card_flop1[i] = *ptr;
            printf("%c", card_flop1[i]);
        }
        printf("\n");
        
        ++ptr;
        printf("card_flop2:");
        for (i = 0; *ptr != '\n'; ++ptr, ++i) {
            card_flop2[i] = *ptr;
            printf("%c", card_flop2[i]);
        }
        printf("\n");
        
        /*跳过“\n/flop \n”,得到flop信息的尾指针*/
        if (strcmp(str_flop, ptr)) {
            ptr += 8;
            break;
        }
    }
    return ptr;
}

/*解析请求消息，用数组分别保存Pid, Jetton, Money, Bet, Action, Pot信息，方便策略函数传参调用*/
char Pid[10] = {'\0'};
char Jetton[10] = {'\0'};
char Money[10] = {'\0'};
char Bet[10] = {'\0'};
char Action[10] = {'\0'};
char Pot[10] = {'\0'};
char *analy_inquire(char *str)
{
    int i;
    char *ptr;
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    /*假设我们的程序*/
    char str_pid[] = {"\n7777"};
    char str_pot[] = {"\ntotal"};
    char str_inquire[] = {"\n/inquire"};
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        if ( strcmp(str_pid, ptr) == 0 )
        {
            printf("i get it\n");
            
            ++ptr;
            printf("Pid:");
            for (i = 0; *ptr != '\0'; ++ptr, ++i) {
                Pid[i] = *ptr;
            }
            printf("%s", Pid);
            printf("\n");
            
            ++ptr;
            printf("Jetton:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Jetton[i] = *ptr;
            }
            printf("%s", Jetton);
            printf("\n");
            
            ++ptr;
            printf("Money:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Money[i] = *ptr;
            }
            printf("%s", Money);
            printf("\n");
            
            ++ptr;
            printf("Bet:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Bet[i] = *ptr;
            }
            printf("%s", Bet);
            printf("\n");
            
            ++ptr;
            printf("Action:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Action[i] = *ptr;
            }
            printf("%s", Action);
            printf("\n");
        }
        
        if (strcmp(str_pot, ptr) == 0)
        {
            /*跳过“\ntotal pot: ”，直接读取pot数值*/
            ptr += 12;
            printf("Pot:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Pot[i] = *ptr;
            }
            printf("%s", Pot);
            printf("\n");
        }
        
        /*跳过"\n/inquire \n”,得到inquire信息的尾指针*/
        if (strcmp(str_inquire, ptr) == 0)
        {
            ptr += 11;
            break;
        }
    }
    return ptr;
}

/*解析手牌消息，一个card_hold数组保存一张手牌内容，方便策略函数传参调用*/
char card_hold0[10] = {'\0'};
char card_hold1[10] = {'\0'};
char *analy_hlod(char *str)
{
    int i;
    char *ptr;
    char str_hold[] = {"\n/hold"};
    /*用“\n”分割buffer信息*/
    char *delim = "\n";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        printf("card_hold0:");
        for (i = 0; *ptr != '\0'; ++ptr, ++i) {
            card_hold0[i] = *ptr;
            printf("%c", card_hold0[i]);
        }
        printf("\n");
        
        ++ptr;
        printf("card_hold1:");
        for (i = 0; *ptr != '\n'; ++ptr, ++i) {
            card_hold1[i] = *ptr;
            printf("%c", card_hold1[i]);
        }
        printf("\n");
        
        /*跳过“\n/hold \n”,得到hold信息的尾指针*/
        if (strcmp(str_hold, ptr)) {
            ptr += 8;
            break;
        }
    }
    return ptr;
}



