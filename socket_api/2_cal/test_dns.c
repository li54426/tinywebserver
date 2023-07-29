#include<stdio.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(int argc, char* argv[]){
    if(argc< 2){
        printf("error");
    }


    struct hostent * host = gethostbyname(argv[1]);
    printf("官方域名是%s\n", host->h_name);
    for(int i = 0; host->h_addr_list[i]; ++i){
        
        printf("ip地址 %d 是%s", i+1, inet_ntoa(*(struct in_addr *)host->h_addr_list[i]) );
    }
    

    return 0;
}