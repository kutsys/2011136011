#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(){
	time_t rawtime;
	struct tm *info;
	while(1){
		time(&rawtime);
		info = localtime(&rawtime);
		printf("localtime : %s", asctime(info));
		sleep(2);
	}
}
