#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
int main(){
	pid_t pid;
	char *path = "/home/appleeji/2011136011/lab6/ptest";
	char cmd;	
	pid = fork();
	if(pid == -1){
		printf("error ouccred during fork()\n");
		exit(1);
	}
	else if(pid == 0){
		execl(path,"ptest",NULL,(char*)0);
	}
	else{
		while(1){
			if(pid != 0) printf("\nrunning\n");
			else printf("\nnon existed\n");
			printf("command input K,Q,S,R :\n");
			scanf("%c", &cmd);
			while(getchar() != '\n');	
			if(cmd == 'Q'){
				if(pid !=0) kill(pid,SIGKILL);	
				 exit(1);
			}
			else if(cmd == 'K') {
				if(pid == 0) continue;
				printf("\nkill child\n");
				kill(pid,SIGKILL);
				pid = 0;
			}
			else if(cmd == 'S') {
				if(pid) printf("\nalready running\n");
				else {
					printf("\nnewly start\n");
					pid = fork();
					if(pid == 0) execl(path,"ptest",NULL,(char*)0);
				}
			}	
			else if(cmd == 'R') {
				if(pid) {
					printf("\nrestart\n");
					kill(pid,SIGKILL);	
					pid = fork();
					if(pid == 0) execl(path,"ptest",NULL,(char*)0);	
				}
				else {
					printf("\nnewly started\n");
					pid = fork();
					if(pid == 0) execl(path,"ptest",NULL,(char*)0);	
				}
			}
			else printf("\nplease input the correct command\n");

 
			sleep(5);
		}
	}

}
