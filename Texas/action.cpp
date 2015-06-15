#include <iostream>
#include<stdlib.h>
#include <sys/socket.h>
#include<time.h>
#include "winpro.h"
//
#include "global.h"
#include "trans.h"
using namespace std;


extern char card_flop0[20];
extern char card_flop1[20];
extern char card_flop2[20];
extern char card_hold0[20];
extern char card_hold1[20];
extern char Pot[20];
extern char turn_card[20];
extern char river_card[20];
// int foldedNum;

extern int is_inquired;
extern int is_holded;
/*int is_floped;
int is_turned;
int is_rivered;*/

extern int m_socket_id;
extern char callNum[10];
extern int n;


//char temp[7][12];
//char a[5][12];

int transform(char*a)
{

   int i=0;
   if(a[0]==0) return 0;
   while(a[i]!=32) {i++;}
   if(a[i+2]==0)return trans[a[0]]+numberadd[a[i+1]];
   else return trans[a[0]]+8;
}
int transform2(char *a)
{
       int i=1;
	   int num=0;
	if(a[0]==0) return 0;
        num=a[0]-48;
		while(a[i]!=0){
			num=num*10;
		     num=num+a[i]-48;
			 i++;
		}
		return num;
}

//0~check  1~call 2~raise 3~all_in  4~fold
int Strategy(double RR)
{
          
           srand((int)time(0));
           int random=rand()%100;
		   if(RR<0.8) {
		        if(random>=5) return 4;
				else return 2;
		   }
		   else if(RR<1.0) {
		         if(random>=20) return 4;
				 else if(random>=15) return 1;
				 else return 2;
		   }
		   else if(RR<1.3){
				 if(random>=40) return 1;
				 else return 2;
		   }
		   else{
		       if(random>=30) return 2;
				 else return 1;
		   }
}


int playn;

void Action()
{

	int n = 4;
	playn = 5;
    int total_pot = 0;
    int thisturn = 0;
    
	printf("ryunn");
    printf("is:%d\n", is_inquired);
    if (is_inquired == 1) {
        total_pot = transform2(Pot);
        thisturn = transform2(callNum);
        for(int i=0;i<20;i++) Pot[i]=0;
        for(int i=0;i<10;i++) callNum[i]=0;
    }
    
    int b[2];
	int a[5];
    //is_holded=1;
    //if (is_holded == 1) {
        b[0]=transform(card_hold0);
        b[1]=transform(card_hold1);
    //}
	
    //if (is_floped == 1) {
        a[0]=transform(card_flop0);
        a[1]=transform(card_flop1);
        a[2]=transform(card_flop2);
    //}
   
    //if (is_turned == 1) {
        a[3]=transform(turn_card);
    //}
	
   // if (is_turned == 1) {
        a[4]=transform(river_card);
    //}

    for(int i=0;i<20;i++) card_hold0[i]=0;
    for(int i=0;i<20;i++) card_hold1[i]=0;
    for(int i=0;i<20;i++) card_flop0[i]=0;
    for(int i=0;i<20;i++) card_flop1[i]=0;
    for(int i=0;i<20;i++) card_flop2[i]=0;
    for(int i=0;i<20;i++) turn_card[i] =0;
    for(int i=0;i<20;i++) river_card[i]=0;

	
    int power = winpro(b, a, n, playn);
    int pot=0;
	int RR=0;
    
    if (total_pot != 0) {
        pot= thisturn / total_pot;
    }
    RR=power/pot;

    int action = Strategy(RR);
    
    /*向server发送action信息*/
    char send_msg[50] = {'\0'};
    
    
    switch(action)       //0~check  1~call 2~raise 3~all_in  4~fold
    {
        case 0:
            snprintf(send_msg, sizeof(send_msg) - 1, "check");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 1:
            snprintf(send_msg, sizeof(send_msg) - 1, "call");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 2:
            snprintf(send_msg, sizeof(send_msg) - 1, "raise");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 3:
            snprintf(send_msg, sizeof(send_msg) - 1, "all_in");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 4:
            snprintf(send_msg, sizeof(send_msg) - 1, "fold");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
    }
}
