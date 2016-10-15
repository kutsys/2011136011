#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(){
	char buf[BUF_SIZE];
	FILE *in, *out;
	int nread;
	int cnt = 0;

	in = fopen("file.zip", "r");
	out = fopen("file.out", "w");

	if(in != NULL && out != NULL) {
		while(!feof(in)){
			nread = fread(buf, 1, BUF_SIZE, in);
			fwrite(buf, 1, nread, out);
			//1바이트가 복사될때 마다 cnt를 올려서 1KB가 
			//복사가 되면 .을 출력해준다
			if(++cnt % 1024 == 0) printf(".");
		}	
		fclose(in);
		fclose(out);
	}
	exit(0);
}
