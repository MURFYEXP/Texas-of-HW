//
//  action.cpp
//  Texas_and_fuck
//
//  Created by mac on 5/28/15.
//  Copyright (c) 2015 mac. All rights reserved.
//

#include <iostream>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include<time.h>
#include "winpro.h"
#include "global.h"
#include "trans.h"
using namespace std;


int transform(char*a)
{
    
    int i=0;
    if(a[0]==0) return 0;
    while(a[i]!=32) {i++;}
    if(a[i+2] != 48)return trans[a[0]]+numberadd[a[i+1]];
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

/*
int Strategy()
{
    
    srand((int)time(0));
    int random=rand()%100;
    
    if(thisturn==0)  
      { 
        if(power<0.1)
           return 4;
  //      else if (random > 40)
  //         return 0;
        else return 2;
       }   
    double pot=0; 
//  thisturn=0;
//total_pot=1243;
    pot=(double) thisturn/(double)total_pot;
    double RR=0;  
    RR=power/pot; 
    
         printf("pot:%f\n", pot); 
  //  printf("what the fuck!!!!!!\n");
    printf("RR:%f\n", RR);
//    printf("thisturn:%d\n", thisturn);
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

*/

int Strategy()
{    
    srand((int)time(0));
    int random=rand()%100;    //≤˙…˙¡ÀÀÊª˙ ˝
    
	//≤ª–Ë“™Õ∂«Æ“≤ø…“‘ÕÊ
    if(thisturn==0)                     
      { 
        if(power<0.1)   return 4;
		else {
		          /*if(random>70) return 2;
				   else return 0;*/
			       return 0;   //÷ª”–check
				}
       }   
    double pot=0; 
	int temp=thisturn;
	if(jetton<temp && jetton>0) temp=jetton;  //≤ª––æÕ◊¢ ÕµÙ
   
	//protect
    if((jetton+ money-temp)<500  &&  power<0.5)  return 4;

    pot=(double) temp/(double)total_pot;    
    double RR=0;  
    RR=power/pot; 
    
	int allin=(int)(temp*3/2);

    if(RR<0.8) {
        if(random>=5) return 4;
        else return 2;
    }
    else if(RR<1.0) {
        if(random>=20) return 4;
        else if(random>=10) return 1;
        else return 2;
    }
    else if(RR<1.3){
        if(random>=40) return 1;
        else 
		{
		  if(random>70 && jetton<allin) return 3;
		  else return 2;
		}
    }
    else{
		if(random>=30){
		    if(random>70 && jetton<allin) return 3;
		   else return 2;
		}
        else return 1;
    }
}


void Action()
{
    
        total_pot = transform2(Pot);
        
        printf("total_pot:%d\n", total_pot);
        printf("thisturn:%d\n",thisturn);
        printf("pre_max:%d\n",pre_max);
     
        b[0]=transform(card_hold0);
        b[1]=transform(card_hold1);
	
        a[0]=transform(card_flop0);
        a[1]=transform(card_flop1);
        a[2]=transform(card_flop2);
    
        a[3]=transform(turn_card);
        a[4]=transform(river_card);
        power = winpro(b, a, n, playn);
        
        int action = Strategy();
        printf("action:%d\n", action);   
        char send_msg[50] = {'\0'};
    
    switch(action)     //0~check  1~call 2~raise 3~all_in  4~fold
    {
        case 0:
            snprintf(send_msg, sizeof(send_msg) - 1, "check \n");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 1:
            snprintf(send_msg, sizeof(send_msg) - 1, "call \n");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            break;
            
        case 2:
            snprintf(send_msg, sizeof(send_msg) - 1, "raise %d \n", 100);
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            pre_max += 100;
            break;
            
        case 3:
            snprintf(send_msg, sizeof(send_msg) - 1, "all_in \n");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            had_all_in = 1;
            break;
            
        case 4:
            snprintf(send_msg, sizeof(send_msg) - 1, "fold \n");
            send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            had_fold = 1;
            break;

        default:
            break;
    }

}

