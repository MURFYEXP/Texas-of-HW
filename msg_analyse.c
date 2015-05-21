/*解析通讯信息v0.1版，目前可解析hold，inquire，flop，turn，river信息。原理：使用strtok函数将缓冲区信息切割成单个的字符串，然后进行筛选匹配；
 由于牌的内容格式均为 color point，所以我们直接在game主函数里面写一个解析花色和点数的函数即可；
 Ps：目前只支持解析以上信息，需要某个信息，再添加即可*/
#include<stdio.h>
#include<string.h>


void analy_hold(char *str);
void analy_inquire(char *str);
void analy_flop(char *str);
void analy_turn_And_river(char *str);


/*解析手牌消息，一个card_hold数组保存一张手牌内容，方便策略函数传参调用*/
char card_hold0[10] = {'\0'};
char card_hold1[10] = {'\0'};
void analy_hlod(char *str)
{
    int i;
    char *ptr;
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
        break;
    }
    
}


int main()
{
    /*根据收到的server信息格式，测试各解析函数*/
    char inquire_buffer[] = {"inquire/ \n7777 1850 8000 50 fold \n4444 1850 8000 0 check \n6666 1850 8000 0 all_in \n2222 1850 8000 0 raise \n1111 1850 8000 0 call \n3333 1850 8000 0 fold \n5555 1950 8000 0 fold \n8888 1900 8000 100 blind \ntotal pot: 800 \ninquire \n"};
    char flop_buffer[] = {"flop/ \nCLUBS A \nCLUBS Q \nDIAMONDS 3 \n/flop \n"};
    char turn_And_river_buffer[] = {"river/ \nSPADES 7 \n/river \n"};
    char hold_buffer[] = {"hold/ \nCLUBS K \nCLUBS 4 \n/hold \n"};
    
    analy_inquire(inquire_buffer);
    analy_flop(flop_buffer);
    analy_turn_And_river(turn_And_river_buffer);
    analy_hlod(hold_buffer);
}


/*解析转牌，河牌消息，一个one_hold数组保存一张手牌内容，方便策略函数传参调用*/
char one_card[10] = {'\0'};
void analy_turn_And_river(char *str)
{
    int i;
    char *ptr;
    /*用“\n”分割buffer信息*/
    char *delim = "\n";
    strtok(str, delim);
    while ( (ptr = strtok(NULL, delim)) != NULL )
    {
        printf("one_card:");
        for (i = 0; *ptr != '\0'; ++ptr, ++i) {
            one_card[i] = *ptr;
            printf("%c", one_card[i]);
        }
        printf("\n");
        break;
    }
}

/*解析公牌消息，一个card_flop数组保存一张手牌内容，方便策略函数传参调用*/
char card_flop0[10] = {'\0'};
char card_flop1[10] = {'\0'};
char card_flop2[10] = {'\0'};
void analy_flop(char *str)
{
    int i;
    char *ptr;
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
        
        break;
    }
}

/*解析请求消息，用数组分别保存Pid, Jetton, Money, Bet信息，方便策略函数传参调用*/
char Pid[10] = {'\0'};
char Jetton[10] = {'\0'};
char Money[10] = {'\0'};
char Bet[10] = {'\0'};
char Action[10] = {'\0'};
char Pot[10] = {'\0'};
void analy_inquire(char *str)
{
    int i;
    char *ptr;
    /*用“ ”分割buffer信息*/
    char *delim = " ";
    /*假设我们的程序*/
    char str_pid[] = {"\n8888"};
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
                printf("%c", Pid[i]);
            }
            printf("\n");
            
            ++ptr;
            printf("Jetton:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Jetton[i] = *ptr;
                printf("%c", Jetton[i]);
            }
            printf("\n");
            
            ++ptr;
            printf("Money:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Money[i] = *ptr;
                printf("%c", Money[i]);
            }
            printf("\n");
            
            ++ptr;
            printf("Bet:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Bet[i] = *ptr;
                printf("%c", Bet[i]);
            }
            printf("\n");
            
            /*跳过“ blind \ntotal pot: ”，直接读取pot数值*/
            ptr += 19;
            printf("Pot:");
            for (i = 0; *ptr != ' '; ++ptr, ++i) {
                Pot[i] = *ptr;
                printf("%c", Pot[i]);
            }
            printf("\n");
            
            break;
        }
    }
}
