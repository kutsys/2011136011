#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 11

int main(){
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char snumber[BUF_SIZE];
	char pid[BUF_SIZE];
	char name[BUF_SIZE]="김민섭";

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "appleeji");
	len = sizeof(address);

	result = connect(sockfd, (struct sockaddr *)&address, len);
	if(result == -1){
		perror("failed socket connection\n");
		exit(1);
	}

	/*읽고 쓰기*/
	read(sockfd, snumber, BUF_SIZE);
	read(sockfd, pid , BUF_SIZE);
	printf("consumer : receving data %s, %s\n", snumber, pid);
	sprintf(pid, "%d", getpid());
	write(sockfd, name, BUF_SIZE);
	write(sockfd, pid, BUF_SIZE);
	close(sockfd);
	exit(0);


}
