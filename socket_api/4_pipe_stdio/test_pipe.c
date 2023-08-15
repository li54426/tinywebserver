#include<unistd.h>
#include<stdio.h>
#include<wait.h>

int main(){
    int fds[2];
    char str1[] = "who are you";
    char str2[]= "thank you";
    char buf[64];
    
    pipe(fds);

    pid_t pid = fork();

    if(pid == 0){
        write(fds[1], str1, sizeof(str1));
        sleep(2);
        read(fds[0], buf, 64);
        printf("i am child, %s\n", buf);

    }
    else{
        read(fds[0], buf, 64);
        printf("i am parent, %s\n", buf);
        write(fds[1], str2, sizeof(str2));
        // sleep(3);

    }
    return 0;
}