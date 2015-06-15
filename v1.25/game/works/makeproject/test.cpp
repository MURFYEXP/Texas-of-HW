#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg_analyes.h"
#include "pokersort.h"
#include "winpro.h"
#include "action.h"

char card_flop0[20];
char card_flop1[20];
char card_flop2[20];
char card_hold0[20];
char card_hold1[20];
char Pot[20];
char turn_card[20];
char river_card[20];
int n;
int playn;
int total_pot;
double power;
int  a[5];
int  b[2];


int foldedNum;
int is_inquired;
int is_holded;
int is_floped;
int is_turned;
int is_rivered;
int thisturn;
char callNum[10];
int m_socket_id = -1;



int main(int argc, char *argv[])
{
    char buffer[2048] = {"seat/ \nbutton: 6666 2000 8000 \nsmall blind: 2222 2000 8000 \nbig blind: 1111 2000 8000 \n4444 2000 8000 \n7777 2000 8000 \n5555 2000 8000 \n8888 2000 8000 \n3333 2000 8000 \n/seat \n"};
    
    char inquire_buffer[] = {"hold/ \nDIAMONDS A \nDIAMONDS 8 \n/hold \ninquire/ \n7777 0 8000 2000 all_in \n3333 0 8000 1000 call \n6666 0 8000 2000 call \n1111 0 8000 2000 all_in \n8888 1900 8000 100 blind \n2222 1950 8000 50 blind \ntotal pot: 815 \n/inquire \nflop \nSPADES 4 \nCLUBS Q \nHEARTS 6 \n/flop \nturn/ \nDIAMONDS 5 \n/turn \nriver \nDIAMONDS A \n/river \n"};
    
    char hold_buffer[] = {"hold/ \nDIAMONDS A \nHEARTS 9 \n/hold \n"};
    
//    is_inquired = 0;
  //  msg_handle(inquire_buffer);
 int i=0,j=1564;
 double t;
t=(double)i/(double)j;
printf("t %f\n",t);
/*    if (is_inquired == 1) {
        Action();
    }*/
}

