#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <pthread.h>

#define BUF_SIZE 11

typedef struct {
	long int my_msg_type;
	char data[BUF_SIZE];
	char pid[BUF_SIZE];
}my_msg_st;

void * thread_send(){
	int msgid_ctop;
	char pid_buffer[BUF_SIZE];	
	my_msg_st some_data;
	sprintf(pid_buffer, "%d", (int)getpid());

	msgid_ctop = msgget((key_t)1235, 0666 | IPC_CREAT);	
	if(msgid_ctop == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	some_data.my_msg_type = 1;
	strcpy(some_data.data,"김민섭");
	strcpy(some_data.pid,pid_buffer);

	if(msgsnd(msgid_ctop, (void*)&some_data,2*BUF_SIZE,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}


};
void * thread_receive(){
	int msgid_ptoc;
	my_msg_st some_data_receive;

	msgid_ptoc = msgget((key_t)1234, 0666 | IPC_CREAT);	
	if(msgid_ptoc == -1){
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if(msgrcv(msgid_ptoc, (void*)&some_data_receive,2*BUF_SIZE,1,0) == -1){
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}
	printf("receiver : receving data %s, %s\n", some_data_receive.data, some_data_receive.pid);
	

};
int main(){
	int i;
	int res;
	pthread_t sender, receiver;
	void * thread_result;
	pid_t fork_result;

	res = pthread_create(&sender,NULL,thread_send, NULL);
	if(res != 0){
		perror("thread sender creation failed");	
		exit(EXIT_FAILURE);	
	}
	res = pthread_create(&receiver,NULL,thread_receive, NULL);
	if(res != 0){
		perror("thread receiver creation failed");	
		exit(EXIT_FAILURE);	
	}

	res = pthread_join(sender, &thread_result);
	if(res == 0){
		printf("picked up a c_sender\n");
	}
	else{
		printf("sender join failed\n");
	}
	res = pthread_join(receiver, &thread_result);
	if(res == 0){
		printf("picked up a c_receiver\n");
	}
	else{
		printf("receiver join failed\n");
	}
	
	exit(EXIT_SUCCESS);
}
