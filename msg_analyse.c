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
char *analy_hold(char *str);
char *analy_inquire(char *str);
char *analy_flop(char *str);
char *analy_turn_And_river(char *str);
char *analy_seat(char *str);
char *analy_showdown(char *str);
char *analy_blind(char *str);
char *analy_pot(char *str);
void msg_handle(char *str);
char *msg_analyse(char *p_bug);

void msg_handle(char *str)
{
    char *ptr;
    char *ptr_msg;
    
    ptr = msg_analyse(str);
    /*粘包信息的处理：解析接收到的信息包，遇到字符串结束符跳出循环*/
    while(*ptr != '\0')
    {
        ptr_msg = msg_analyse(ptr);
        ptr = ptr_msg;
    }
}

static char *p_return;
char *msg_analyse(char *p_bug)
{
    switch (*p_bug) {
        case 'i':
            p_return = analy_inquire(p_bug);
            break;
            
        case 'f':
            p_return = analy_flop(p_bug);
            break;
            
        case 't':
            p_return = analy_turn_And_river(p_bug);
            break;
            
        case 'r':
            p_return = analy_turn_And_river(p_bug);
            break;
            
        case 'h':
            p_return = analy_hold(p_bug);
            break;
            
        case 'b':
            p_return = analy_blind(p_bug);
            break;
            
        case 's':
            if ( *(++p_bug) == 'e') {
                p_return = analy_seat(p_bug);
            }
            else
            {
                p_return = analy_showdown(p_bug);
            }
            break;
            
        case 'p':
            p_return = analy_pot(p_bug);
            break;
            
        default:
            break;
    }
    return p_return;
}

char *analy_blind(char *str)
{
    char *ptr;
    char str_blind[] = {"\n/blind"};
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        /*跳过“\n/blind \n”,得到blind信息的尾指针*/
        if (strcmp(str_blind, ptr) == 0) {
            ptr += 9;
            break;
        }
    }
    return ptr;
}


char *analy_showdown(char *str)
{
    char *ptr;
    char str_show[] = {"\n/showdown"};
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        /*跳过“\n/showdown \n”,得到showdown信息的尾指针*/
        if (strcmp(str_show, ptr) == 0) {
            ptr += 12;
            break;
        }
    }
    return ptr;
}

char *analy_pot(char *str)
{
    char *ptr;
    char str_pot[] = {"\n/pot-win"};
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        /*跳过“\n/pot \n”,得到pot信息的尾指针*/
        if (strcmp(str_pot, ptr) == 0) {
            ptr += 11;
            break;
        }
    }
    return ptr;
}

char *analy_seat(char *str)
{
    char *ptr;
    char str_seat[] = {"\n/seat"};
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        /*跳过“\n/seat \n”,得到seat信息的尾指针*/
        if (strcmp(str_seat, ptr) == 0) {
            ptr += 8;
            break;
        }
    }
    return ptr;
}


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

/*解析请求消息，用数组分别保存Action, Pot信息，方便策略函数传参调用*/
char Action[10] = {'\0'};
char Pot[10] = {'\0'};
char callNum[10] = {'\0'};
int foldedNum = 0;
char *analy_inquire(char *str)
{
    int i;
    char *ptr;
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    /*假设我们的程序*/
    char str_act[] = {"fold"};
    char str_pot[] = {"\ntotal"};
    char str_inquire[] = {"\n/inquire"};
    strtok(str, delim);
    int cnt = 0;
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        ++cnt;
        if (cnt == 4) {
            printf("callNum:");
            for (i = 0; *ptr != '\0'; ++ptr, ++i) {
                callNum[i] = *ptr;
            }
            printf("%s\n", callNum);

            ++ptr;
            printf("Action:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Action[i] = *ptr;
            }
            printf("%s", Action);
            printf("\n");
        }
        
        if (strcmp(str_act, ptr) == 0)
        {
            ++foldedNum;
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
    printf("foldedNum:%d\n", foldedNum);
    return ptr;
}

/*解析手牌消息，一个card_hold数组保存一张手牌内容，方便策略函数传参调用*/
char card_hold0[10] = {'\0'};
char card_hold1[10] = {'\0'};
char *analy_hold(char *str)
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



