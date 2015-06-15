#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg_analyes.h"
#include "action.h"

char card_flop0[20];
char card_flop1[20];
char card_flop2[20];
char card_hold0[20];
char card_hold1[20];
char Money[20];
int  money;
char Pot[20];
char turn_card[20];
char river_card[20];
int n;
int playn;
int total_pot;
double power;
int  a[5];
int  b[2];
char callNum[100];

int my_id;
int id_len;
char Jetton[20];
int jetton;
char str_pid[10];

int pre_max = 0;
int foldedNum;
int is_inquired;
int is_holded;
int is_floped;
int is_turned;
int is_rivered;
int had_all_in;
int had_fold;

int thisturn;
int m_socket_id = -1;

/* 处理server的消息 */
int on_server_message(int length, const char* buffer)
{
    printf("Recieve Data From Server(%s)\n", buffer);
    
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        printf("Usage: ./%s server_ip server_port my_ip my_port my_id\n", argv[0]);
        return -1;
    }
    
    /* 获取输入参数 */
    in_addr_t server_ip = inet_addr(argv[1]);
    in_port_t server_port = htons(atoi(argv[2]));
    in_addr_t my_ip = inet_addr(argv[3]);
    in_port_t my_port = htons(atoi(argv[4]));
    my_id = atoi(argv[5]);

    
    /* 创建socket */
    m_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket_id < 0)
    {
        printf("init socket failed!\n");
        return -1;
    }
    
    /* 设置socket选项，地址重复使用，防止程序非正常退出，下次启动时bind失败 */
    int is_reuse_addr = 1;
    setsockopt(m_socket_id, SOL_SOCKET, SO_REUSEADDR, (const char*)&is_reuse_addr, sizeof(is_reuse_addr));
    
    /* 绑定指定ip和port，不然会被server拒绝 */
    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = my_ip;
    my_addr.sin_port = my_port;
    if(bind(m_socket_id, (struct sockaddr*)&my_addr, sizeof(my_addr)))
    {
        printf("bind failed!\n");
        return -1;
    }
    
    /* 连接server */
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = server_ip;
    server_addr.sin_port = server_port;
    while(connect(m_socket_id, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        usleep(100*1000); /* sleep 100ms, 然后重试，保证无论server先起还是后起，都不会有问题 */
    }
    
    /* 向server注册 */
    char reg_msg[50] = {'\0'};
    snprintf(reg_msg, sizeof(reg_msg) - 1, "reg: %d %s \n", my_id, "tt");
    send(m_socket_id, reg_msg, strlen(reg_msg) + 1, 0);
   
    /*向server发送action信息*/
    char send_msg[50] = {'\0'};
    snprintf(send_msg, sizeof(send_msg) - 1, "call \n");
    
    FILE *fp;
    fp = fopen("/home/yow-yow/Desktop/data", "w");
    char *ptr;
    /* 接收server消息，进入游戏 */
    int i = 5;
    while(1)
    {
        char buffer[2048] = {'\0'};
        int length = recv(m_socket_id, buffer, sizeof(buffer) - 1, 0);
        /*将接受到的请求信息写入文件，用于解析信息采取相应的响应*/
  //   fprintf(fp, "buffer:%s\n", buffer);
     
        if(length > 0)
        {
            /* on_server_message返回-1（比如收到game over消息），则跳出循环，关闭socket，安全退出程序 */
            if (-1 == on_server_message(length, buffer))
            {
                break;
            }
            
//          send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            /*解析通讯信息*/
            is_inquired = 0;
            had_all_in = 0;
            had_fold = 0;
           // had_all_in = 0;
//            is_holded = 0;
                 msg_handle(buffer);
           if (is_inquired == 1) {
           if(is_holded==1)
            {
                 is_holded=0;
                  send(m_socket_id, send_msg, strlen(send_msg) + 1, 0);
            } 
            if( (had_all_in == 1) || (had_fold == 1) )
             {
             }
               else
               {
               Action();
               }
          //    fprintf(fp,"action :%d\n",action);
         //      fprintf(fp,"pre_max :%d\n", pre_max);

           //    fprintf(fp,"max :%d\n", max);
              
             //  fprintf(fp,"power:%f\n",power);
              
             }
        }
}    
    /* 关闭socket */
    close(m_socket_id);
}
