#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/shm.h>
#define BUF_SIZE 11 
typedef struct {
	char snumber[BUF_SIZE];
	char name[BUF_SIZE];
	char pid[BUF_SIZE];
	short flag;
}shared_use_st;
int main(){
	
	shared_use_st * provider_st;

	void* shared_memory = NULL;
	int shmid;
	
	char snumber[BUF_SIZE];
	char name[BUF_SIZE];
	char pid_c[BUF_SIZE];

	int pid = (int)getpid();
	sprintf(pid_c, "%d", pid); 
	//쉐어드 메모리 생성 키캆1234, 사이즈구조체크기, 권한,생성후존재시값반환
	shmid = shmget((key_t)1234, sizeof(shared_use_st), 0666 | IPC_CREAT);
	//sprintf(shmid_c, "%d", shmid);
	
	if( shmid == -1){
		fprintf(stderr, "shmget failure");
		exit(EXIT_FAILURE);
	}
	//생성된 쉐어드 메모리에 내 매모리 같다 붙이기
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		fprintf(stderr, "shmat failure");
		exit(EXIT_FAILURE);
	}
	//붙여진 메모리에 형변환 해서 내 구조체가 가르키게 하기
	provider_st = (shared_use_st*)shared_memory;
	//busywait을 위한 스타트
	provider_st->flag = 2;

	//fork exec를 이용해서 consumer생성	
	pid_t fork_result;
	fork_result = fork();
	if(fork_result == (pid_t)-1){
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}
	else if(fork_result == 0){
		(void)execl("ipc_consumer", "ipc_consumer",NULL,NULL);
		exit(EXIT_FAILURE);
	}

	//쉐어드 메모리의 학번, pid값을 producer값으로 셋팅후 flag이용해 busywait 탈출
	strcpy(provider_st->snumber,"2011136011");
	strcpy(provider_st->pid,pid_c);
	provider_st->flag = 0;

	//consumer에서 busywait탈출후 producer에게 flag신호 던져줄때까지 기다림
	while(provider_st->flag != 1){}

	strcpy(name,provider_st->name);
	strcpy(pid_c,provider_st->pid);
	
	printf("producer : receving data %s, %s\n", name, pid_c);
	
	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmget failure");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);

}





