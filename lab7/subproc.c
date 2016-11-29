#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NUM_REPEAT 20

int main(){
	struct tm *t;
	int r;
	time_t _time;
	int count=0;
	
	while(1){	
		srand(time(NULL));
		r = rand()%20;
		_time = time(NULL);
		t = localtime(&_time);
		printf("process_num : %d  time : %d년%d월%d일 %d시 %d분 %d초   call count = %d\n",getpid(),t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec, ++count);
		sleep(r);
		if(count == NUM_REPEAT) break;
	}	
}
