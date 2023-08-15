#include<sys/wait.h>

#include<stdio.h>


int main(){
    pid_t pid = fork();
    int status;
    if(pid == 0){
        sleep(5);
        exit(24) ;
    }
    else{
        
        while(!waitpid(-1, &status, WNOHANG) ){
            sleep(3);
            puts("sleep 3 s");
        }
    }

    printf("%d", status);

    if(WIFEXITED(status)){
        printf("child send %d \n", WIFEXITED(status));
    }
    return 0;

}