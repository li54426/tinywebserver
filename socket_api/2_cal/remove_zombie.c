#include<stdio.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

// #define _XOPEN_SOURCE 700

#include<signal.h>
#include<sys/wait.h>

void read_childproc(int sig){
    int status;
    pid_t id = waitpid(-1, &status, WNOHANG);

    if(WIFEXITED(status)){
        printf("the child pid = %d\n", id);
        printf("child send %d\n", WEXITSTATUS(status));
    }

}


int main(){
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid_t pid = fork();

    if(pid == 0){
        puts("i am a child process");
        sleep(10);
        return 12;
    }

    else{
        printf("child pid = %d\n", pid);
        pid = fork();

        if(pid == 0){
            puts("i am child process");
            sleep(10);
            exit(24);
        }
        else{
            //int i ;
            printf("child pid = %d\n", pid);

            for(int i =0; i<5; i++){
                puts("wait...");
                sleep(5);
            }
        }
    }

    return 0;
}