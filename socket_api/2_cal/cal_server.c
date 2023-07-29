#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


void errhandling(char * c);
int main(int argc, char * argv[]){
    if(argc<2){
        errhandling("argc error");
    }

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv_addr, clnt_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // 获得指定端口
    int flag = bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    if(flag == -1){
        errhandling("bind error");
    }

    listen(serv_sock, 4);
    char buf [1024];
    socklen_t len = sizeof(clnt_addr);

    while(1){
        // 需要地址来存放对面是谁
        int clnt_sock = accept(serv_sock, (struct sockaddr *)& clnt_addr, &len);
        if(clnt_sock ==-1){
            errhandling("accept error");
        }

        read(clnt_sock, buf, 1024);

        int size = 4;
        int n = buf[0];
        char op = buf[1];
        int start = 2;
        int nums[1024];

        int res = *(int*)(buf +2);

        printf("n=%d, op= %c, ", n, op);

        
        for(int i =1; i<n; ++i){
            int temp = *(int*) (buf+ start + size *i);
            printf("the num = %d", temp);

            if(op == '*')res *=temp;
            else if(op=='/') res /= temp;
            else if(op == '+') res += temp;
            else{
                res -= temp;
            }

        }
        write(clnt_sock, &res, 4);
        close(clnt_sock);

        printf("the res = %d , and trans success and close success\n", res);
    }
    return 0;




}



void errhandling(char * c){
    fputs(c, stdout);
    fputc('\n', stdout);
    exit(1);
}