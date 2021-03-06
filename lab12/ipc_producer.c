#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

#define BUF_SIZE 11

typedef struct {
	long int my_msg_type;
	char data[BUF_SIZE];
	char pid[BUF_SIZE];
}my_msg_st;

int main(){
	int msgid_ptoc;
	int msgid_ctop;
	my_msg_st some_data;
	my_msg_st some_data_receive;
	char pid_buffer[BUF_SIZE];	
	char buffer[BUF_SIZE];
	pid_t fork_result;

	sprintf(pid_buffer, "%d", (int)getpid());
	
	fork_result = fork();
	if(fork_result == (pid_t)-1){
		fprintf(stderr, "fork failure");	
		exit(EXIT_FAILURE);
	}
	else if(fork_result == 0){
		(void)execl("ipc_consumer","ipc_consumer",NULL,NULL);
		exit(EXIT_FAILURE);
	}
	//send (p to c)
	msgid_ptoc = msgget((key_t)1234, 0666 | IPC_CREAT);	
	if(msgid_ptoc == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	some_data.my_msg_type = 1;
	strcpy(some_data.data,"2011136011");
	strcpy(some_data.pid,pid_buffer);

	if(msgsnd(msgid_ptoc, (void*)&some_data,2*BUF_SIZE,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}

	//receive (c to p)
	msgid_ctop = msgget((key_t)1235, 0666 | IPC_CREAT);	
	if(msgid_ctop == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msgid_ctop, (void*)&some_data_receive,2*BUF_SIZE,1,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	printf("producer : receving data %s, %s\n", some_data_receive.data, some_data_receive.pid);
	exit(EXIT_SUCCESS);



}
