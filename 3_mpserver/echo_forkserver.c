#include <sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>

#include<unistd.h>

#include<string.h>

#include<signal.h>

#include<sys/wait.h>

#define BUFF_SIZE 64
void error_handing(char *s);


void childhandle(int seg){
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id %d\n", pid);
}



void regact(struct sigaction *act){
    act-> sa_handler = childhandle;
    // act-> 
}



int main(int argc, char *argv[]){
    if(argc!= 2){
        printf("the server program run fail");
        exit(1);
    }

    int serv_sock, clnt_sock;
    char message[BUFF_SIZE];
    int str_len;

    // signal 设置
    struct sigaction act;
    act.sa_handler = childhandle;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    int state = sigaction(SIGCHLD, &act, 0);


    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1){
        error_handing("socket() error");
    }

    struct sockaddr_in serv_addr, clnt_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));


    int flag = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr) );
    if(flag == -1){
        error_handing("bind error");
    }

    if(listen(serv_sock, 5) == -1){
        error_handing("listen error");
    }

    while(1){
        socklen_t len = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &len);

        if(clnt_sock == -1){
            continue;
        }
        puts("...connected...");

        pid_t pid = fork();

        // 提供服务
        if(pid == 0){
            close(serv_sock);
            
            while(( read(clnt_sock, message, 200) )!=0){
                str_len = strlen(message);
                write(clnt_sock, message, strlen);
            }
            close(clnt_sock);
            puts("connected is killed");
            return 0;
        }
        else{
            close(clnt_sock);
        }

    }

    close(serv_sock);
    return 0;
    


}

void error_handing(char *s){
    // printf("");
    fputs(s, stderr);
    fputc('\n', stderr);
    exit(1);
}