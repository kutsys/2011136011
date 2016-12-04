#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_SIZE 11
#define FIFO "./fifo"

int main(){ 
	char buffer_w[BUF_SIZE];
	char buffer_r[BUF_SIZE];

	int fp_w;
	int fp_r;

	int nread;
	int res;

	char snumber[BUF_SIZE];
	char pid_buffer[BUF_SIZE];
	char name[] = "김민섭";
	int pid = (int)getpid();

	memset(buffer_w, '\0', BUF_SIZE);
	memset(buffer_r, '\0', BUF_SIZE);


	if((fp_r = open(FIFO, O_RDONLY)) < 0){
		fprintf(stderr, "c_r open error\n");
		exit(EXIT_FAILURE);
	}
/*
	if((fp_w = open(FIFO_C, O_RDONLY)) < 0){
		fprintf(stderr, "open error\n");
		exit(EXIT_FAILURE);
	}
*/
	read(fp_r, buffer_r, BUF_SIZE);
	strcpy(snumber, buffer_r);	
	read(fp_r, buffer_r, BUF_SIZE);
	strcpy(pid_buffer, buffer_r);	
	printf("consumer : receving data %s, %s\n", snumber, pid_buffer);

	close(fp_r);
/*	
	if(access(FIFO_C, F_OK) == -1){
		res = mkfifo(FIFO_C, 0777);
		if(res != 0){
			fprintf(stderr, "consumer 피포파일 생성 불가 %s\n", FIFO_C);
			exit(EXIT_FAILURE);
		}
	}	
*/	
	if((fp_w = open(FIFO, O_WRONLY | O_NONBLOCK))<0){
		fprintf(stderr, "c_w open error\n");
		exit(EXIT_FAILURE);
	}
	
	sprintf(pid_buffer, "%d", pid);	
	write(fp_w, name, BUF_SIZE);
	write(fp_w, pid_buffer, BUF_SIZE); 	
	close(fp_w);
	sleep(2);
	exit(EXIT_SUCCESS);
}












