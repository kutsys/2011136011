#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/un.h>
#include <stdlib.h>

#define BUF_SIZE 11

int main(){
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	char snumber[BUF_SIZE] = "2011136011";	
	char pid[BUF_SIZE];	
	char name[BUF_SIZE];
	sprintf(pid, "%d", (int)getpid());

	unlink("appleeji");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "appleeji");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr*)&server_address, server_len);
	
	listen(server_sockfd, 5);

	client_len = sizeof(client_address);
	client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);

	/*쓰고 읽기*/
	/*소켓으로 서버와 클라이언트가 연결되면 서버의 데이터를 클라이언트가 받지 않더라도 서버가 읽어들이지 않는다 pipe2개 뚫은 효과 */
	write(client_sockfd, snumber, BUF_SIZE);
	write(client_sockfd, pid, BUF_SIZE);
	read(client_sockfd, name, BUF_SIZE);
	read(client_sockfd, pid, BUF_SIZE);
	close(client_sockfd);
	printf("producer : receving data %s, %s\n",name, pid);

}
