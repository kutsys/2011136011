#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define NUM_PROCESS 10


int main(){
	int count = 0;	
	char ch_buf[20];
	int pid;
	int pid_ary[NUM_PROCESS];
	int i;
	//프로그램 스타트	
	printf("시작하려면 start를 입력하시오 :");
	while(1){
		fgets(ch_buf, 10, stdin);
		if(strncmp("start", ch_buf, 5) == 0){
			break;
		}
	}
	
	while(1){
		pid = fork();
		if(pid == -1){
			printf("error fork()\n");
			exit(1);
		}
		else if(pid == 0){
			(void)execl("subproc","subproc",NULL,NULL);
		}
		else{
			pid_ary[count] = pid;
		}
		if(++count >= 10) break;
	}
	for(i = 0; i<NUM_PROCESS; i++){
		wait(&pid_ary[i]);
	}	
	printf("Fisihed (process)\n");
	exit(EXIT_SUCCESS);
}	
