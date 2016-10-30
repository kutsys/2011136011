#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <stdio_ext.h>

//return ptest's pid
pid_t getPtestPid(){
	FILE *cmd;
	char line[20];
	pid_t pid;
	if((cmd = popen("pidof ptest", "r")) == NULL){
		printf("popen error\n");
	}
	fgets(line,20,cmd);
	pid = strtoul(line,NULL,10);	
	pclose(cmd);
	
	return pid;
}

void ptestMon(int sig){
	pid_t pid = getPtestPid();
	if(pid) printf("\nrunning\n");
	else printf("\nthere is no process\n");
	fflush(stdout);
	alarm(3);
}

int main(){
	pid_t pid = 0;
	char cmd;	
	while(1){
		(void) signal(SIGALRM, ptestMon);
		alarm(3);

		printf("command input K,Q,S,R :\n");
		scanf("%c", &cmd);
		while(getchar() != '\n');
		//__fpurge(stdin);	
		if(cmd == 'Q'){
			 exit(1);
		}
		else if(cmd == 'K') {
			pid = getPtestPid();
			if(pid == 0) {
				printf("there is no process\n");	
				continue;
			}
			else {
				printf("\nkill child\n");	
				kill(pid,SIGKILL);
				pid = 0;
			}
		}
		else if(cmd == 'S') {
			pid = getPtestPid();
			if(pid) printf("\nalready running\n");
			else {
				printf("\nnewly start\n");
				system("gnome-terminal --command \"./ptest\"");
			}
		}	
		else if(cmd == 'R') {
			pid = getPtestPid();
			if(pid) {
				printf("\nrestart\n");
				kill(pid,SIGKILL);	
				system("gnome-terminal --command \"./ptest\"");	
			}
			else {
				printf("\nnewly started\n");
				system("gnome-terminal --command \"./ptest\"");
			}
		}
		else printf("\nplease input the correct command\n");
 
		sleep(2);
	}
}

