#include<sys/socket.h>
#include<stdio.h>

#include<stdlib.h>
#include<string.h>

#include<unistd.h> 

#include <arpa/inet.h>
// #include <netinet/in.h>
void errhandling(char * c);

int main(int argc, char * argv[]){
    // printf("请输入ip地址 和端口");
    if(argc< 3){
        errhandling("argc error");
    }

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        errhandling("socket error");
    }

    // **只需要知道对面是谁, 剩下的交给操作系统**
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr) );

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // 两步, char* -> int , 再转换字节序
    serv_addr.sin_port = htons(atoi(argv[2]));

    int flag = connect(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    if(flag == -1){
        errhandling("connect error");
    }

    puts("-----connect success----");

    char message [1024];
    while(1){
        // 尽可能少的发送次数, 也就是在客户端所有的数据准备好了再发送
        puts("iput the numbers (q to exit)");
        
        // fgets() 函数会读取并保留换行符。
        fgets(message, 1024, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")){
            break;
        }


        int n = atoi(message);
        char c = (char)n;
        // printf("c= %c", c);
        message[0] = (char)n;
        // printf("n=%d", n);
        // printf("message[0]= %c", message[0]);
        
        puts("choose the operation, you can write + - * /");
        fgets(message+1, 1024, stdin);
        int size = 4;
        int start = 2;


        // puts("\n");

        for(int i = 0; i<n; ++i){
            printf("you need write the %d number", i+1);
            scanf("%d", (int *)(message+start + i * size) );
            printf("check the num is %d\n", *(int *)(message+start + i * size));
        }

        message[n* size + start] = 0;

        int str_len = n* size + start;
        // strlen(message);

        printf("the len = %d, all the message is %s\n",str_len,  message);
        flag = write(serv_sock, message, str_len);

        memset(message, 'a', 1024);
        if(flag == -1){
            errhandling("write error");
        }

        int res = 0;

        read(serv_sock, &res, 4);
        printf("the answer is %d\n\n\n", res);


    }
    close(serv_sock);
    return 0;








    return 0;
}

void errhandling(char * c){
    fputs(c, stdout);
    fputc('\n', stdout);
    exit(1);
}