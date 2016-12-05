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

	sprintf(pid_buffer, "%d", (int)getpid());
	
	//receive (p to c)
	msgid_ptoc = msgget((key_t)1234, 0666 | IPC_CREAT);	
	if(msgid_ptoc == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msgid_ptoc, (void*)&some_data,2*BUF_SIZE,1,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	strcpy(some_data_receive.data,some_data.data);
	strcpy(some_data_receive.pid,some_data.pid);
	printf("consumer : receiving data %s, %s\n", some_data_receive.data, some_data_recive.pid);

	//receive (p to c)
	msgid_ctop = msgget((key_t)1235, 0666 | IPC_CREAT);	
	if(msgid_ctop == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msgid_ctop, (void*)&some_data,2*BUF_SIZE,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	some_data.my_msg_type = 2;
	strcpy(some_data.data, "name");
	strcpy(some_data.pid, pid_buffer);	
	exit(EXIT_SUCCESS);

}
