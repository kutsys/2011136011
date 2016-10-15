#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 1024

int main(){
	char block[BUF_SIZE];
	int in, out;
	int nread;
	int cnt = 0;
		
	in = open("file.zip", O_RDONLY);
	out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

	while((nread = read(in,block,BUF_SIZE)) > 0){
		write(out,block,nread);	cnt++;
		//파일을 복사하는 과정에서 .을 출력해주기 위해서
		//1KB마다 .이출력되게 1바이트가 복사될때 마다 cnt를 올린다
		if(cnt % 1024 == 0) printf(".");	
	}
	exit(0);	
}
