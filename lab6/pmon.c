#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
int main(){
	pid_t pid;
	char * msg;
	time_t rawtime;
	struct tm *info;
	char cmd;	
	pid = fork();
	if(pid == -1){
		printf("error ouccred during fork()\n");
		exit(1);
	}
	else if(pid == 0){
		execl("/home/appleeji/lab6/ptest","ptest",NULL,(char*)0);
	}
	else{
		while(1){
			printf("command input K,Q,S,R :\n");
			scanf("%c", &cmd);
			if(cmd == 'Q'){
				if(pid !=0) kill(pid,SIGKILL);	
				 exit(1);
			}
			else if(cmd == 'K') {
				if(pid == 0) continue;
				printf("kill child\n");
				kill(pid,SIGKILL);
				pid = 0;
			}
			else if(cmd == 'S') {
				if(pid) printf("already running\n");
				else {
					printf("newly start\n");
					pid = fork();
					if(pid == 0) execl("/home/appleeji/lab6/ptest","ptest",NULL,(char*)0);
				}
			}	
			else if(cmd == 'R') {
				if(pid) {
					printf("restart\n");
					kill(pid,SIGKILL);	
					pid = fork();
					if(pid == 0) execl("/home/appleeji/lab6/ptest","ptest",NULL,(char*)0);	
				}
				else {
					printf("newly started\n");
					pid = fork();
					if(pid == 0) execl("/home/appleeji/lab6/ptest","ptest",NULL,(char*)0);	
				}
			}
			else continue;
 
			sleep(5);
		}
	}

}
