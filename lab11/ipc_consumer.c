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
int main(int argc, char * argv[]){
	
	shared_use_st * provider_st;

	void* shared_memory = NULL;
	int shmid;
	int i;
	
	char snumber[BUF_SIZE];
	char name[BUF_SIZE];
	char pid_p[BUF_SIZE];

	int pid;
	shmid = shmget((key_t)1234, sizeof(shared_use_st), 0666 | IPC_CREAT);

	if( shmid == -1){
		fprintf(stderr, "shmget failure");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1){
		fprintf(stderr, "shmat failure");
		exit(EXIT_FAILURE);
	}	
	provider_st = (shared_use_st*)shared_memory;
	
	//busywait
	while(provider_st->flag != 0){
	}
	strcpy(snumber,provider_st->snumber);
	strcpy(pid_p,provider_st->pid);
	printf("consumer : receving data %s, %s\n", snumber, pid_p);

	//받은값 출력후 쉐어드 메모리값 consumer값으로 셋팅후 플레그로 신호줌	
	pid = (int)getpid();	
	sprintf(pid_p, "%d", pid);	
	strcpy(provider_st->name,"김민섭");
	strcpy(provider_st->pid,pid_p);
 	provider_st->flag = 1;

	
	if(shmdt(shared_memory) == -1){
		fprintf(stderr, "shmdt failure");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	
}







