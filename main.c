//
//  main.c
//  各种测试用
//
//  Created by mac on 2/13/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

/*解析通讯信息v1.0版，可支持粘包信息的处理*/
#include<stdio.h>
#include<string.h>
#include "msg_analyse.h"
char *msg_analyse(char *p_bug);
void msg_handle(char *str);

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

char *p_return;
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
            p_return = analy_hlod(p_bug);
            break;
            
        default:
            break;
    }
    return p_return;
}

int main()
{
    /*根据收到的server信息格式，测试各解析函数*/
    char buffer[] = {"inquire/ \n7777 1850 8000 50 fold \n4444 1850 8000 0 check \n6666 1850 8000 0 all_in \n2222 1850 8000 0 raise \n1111 1850 8000 0 call \n3333 1850 8000 0 fold \n5555 1950 8000 0 fold \n8888 1900 8000 100 blind \ntotal pot: 1000 \n/inquire \nflop/ \nCLUBS A \nCLUBS Q \nDIAMONDS 3 \n/flop \nriver/ \nSPADES 7 \n/river \nhold/ \nCLUBS K \nCLUBS 4 \n/hold \n"};
    char flop_buffer[] = {"flop/ \nCLUBS A \nCLUBS Q \nDIAMONDS 3 \n/flop \n"};
    char turn_And_river_buffer[] = {"river/ \nSPADES 7 \n/river \n"};
    char hold_buffer[] = {"hold/ \nCLUBS K \nCLUBS 4 \n/hold \n"};
    msg_handle(buffer);
}


