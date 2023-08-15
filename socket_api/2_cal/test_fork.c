#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>

int g = 10;

int main(){
    int l = 20;
    g++; 
    l++;

    pid_t p = fork();

    if(p ==0 ){
        g+=10;
        l +=10;
        printf("pid == 0, g=%d, l =%d\n", g, l);
    }
    else{
        g-=10;
        l-=10;
        printf("pid !=0, g=%d, l =%d\n", g, l);
    }
    // pid !=0, g=1, l =11
    // pid == 0, g=21, l =31
    return 0;
}