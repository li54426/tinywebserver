#include <sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>

#include<unistd.h>

#include<string.h>
#define BUFF_SIZE 64
void error_handing(char *s);

int main(int argc, char *argv[]){
    if(argc!= 2){
        printf("the server program run fail");
        exit(1);
    }

    int serv_sock, clnt_sock;
    char message[BUFF_SIZE];
    int str_len;

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

    for(int i = 0; i<5; ++i){
        socklen_t len = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &len);
        if(clnt_sock == -1){
            error_handing("accept wrong");
        }
        printf("connected client %d \n", i+1);

        while((str_len = read(clnt_sock, message, BUFF_SIZE)) !=0){
            write(clnt_sock, message, str_len);
        }
        close(clnt_sock);


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