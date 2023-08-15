# include <arpa/inet.h>
# include<stdio.h>

int main(){
    unsigned int a;
    unsigned long b;
    printf("unsigned long size = %lu\n", sizeof(b));
    printf("unsigned int size = %lu\n", sizeof(a));
    printf("int size = %lu\n", sizeof(int));

    char *addr1 = "1.2.3.4";
    char *addr2 = "192.168.123.1";
    unsigned int conv_addr = inet_addr(addr1);

    if(-1 != conv_addr){
        printf("Network ordered integer addr: %#x \n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if(-1 != conv_addr){
        printf("Network ordered integer addr: %#x \n", conv_addr);
    }

    return 0;
}