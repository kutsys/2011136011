#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_P "./fifo_p"
#define FIFO_C "./fifo_c"
#define BUF_SIZE 11

int main(){
	
	int fp_r;
	int fp_w;
	char snumber[] = "2011136011";
	char name[BUF_SIZE];
	char buffer_r[BUF_SIZE];
	char buffer_w[BUF_SIZE];
	
//	char buffer[BUF_SIZE];

	pid_t fork_result ;
	int  pid = (int)getpid();
	char pid_buffer[BUF_SIZE] ;
	int res;

	sprintf(pid_buffer, "%d", pid);


	if(access(FIFO_P, F_OK) == -1){
		res = mkfifo(FIFO_P, 0666);
		if(res != 0){
			fprintf(stderr, "producer 피포파일 생성 불가 %s\n",FIFO_P);
			exit(EXIT_FAILURE);
		}	
	}
	// 1은 쓰기용
	if((fp_w = open(FIFO_P, O_RDWR | O_NONBLOCK )) < 0 ){
		fprintf(stderr, "p dopen error\n");
		exit(EXIT_FAILURE);
	}

	memset(buffer_w, '\0', BUF_SIZE); 
	memset(buffer_r, '\0', BUF_SIZE);

	//버퍼의 값을 NULL로 초기화 한다
//	memset(buffer, '\0', sizeof(buffer));	


	fork_result = fork();
	if(fork_result == (pid_t)-1) {
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}
	if(fork_result == 0){
		//읽기용 파일디스크립터 file_pipes[0]을 버퍼에 써서 consumer에게준다
		(void)execl("ipc_consumer" ,"ipc_consumer",NULL,NULL);
		exit(EXIT_FAILURE);
	}
	else{
		write(fp_w, snumber, BUF_SIZE);
		write(fp_w, pid_buffer, BUF_SIZE);
	}
		close(fp_w);
	if((fp_r = open(FIFO_C, O_RDWR))<0){
		fprintf(stderr, "c open error\n");
		exit(EXIT_FAILURE);
	}

	read(fp_r, buffer_r, BUF_SIZE);
	strcpy(name,buffer_r);
	read(fp_r, buffer_r, BUF_SIZE);
	strcpy(pid_buffer, buffer_r);
	printf("producer : receving data %s, %s\n", name, pid_buffer);
	close(fp_r);
	exit(EXIT_SUCCESS);
}
