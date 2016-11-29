#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

#define NUM_THREAD 10
#define NUM_REPEAT 20

sem_t bin_sem;
int	count[NUM_THREAD];
void * thread_function(void * arg);

int main(){
	int res;
	int i;
	pthread_t a_thread[NUM_THREAD];
	void * thread_result;
	char ch_buf[20];
	//세마포 인잇
	res = sem_init(&bin_sem, 0, 0);

	if(res != 0){
		perror("Thread creation failed");
		exit(EXIT_FAILURE);	
	}	
		
	for(i = 0; i<NUM_THREAD; i++){
		count[i] = 0;	
	}
	//쓰레드 다중 생성
	for(i = 0; i<NUM_THREAD; i++){
		res = pthread_create(&(a_thread[i]), NULL, thread_function, (void *)&i);
		if(res != 0){
			perror("Thread creation failed");
			exit(EXIT_FAILURE);	
		}	
		sleep(1);
	}
	//세마포 시작
	printf("시작하려면 start를 입력하시오 :");
	while(1){
		fgets(ch_buf, 10, stdin);
		if(strncmp("start", ch_buf, 5) == 0){
			sem_post(&bin_sem);
			break;
		}
	}
	//쓰레드 다중 조인	
	for(i = NUM_THREAD-1; i>=0; i--){
		res = pthread_join(a_thread[i], &thread_result);
		if(res == 0){
			printf("Picked up a thread\n");
		}
		else {
			perror("pthread_join failed");
		}
	}
	printf("Fisihed (Thread)\n");
	exit(EXIT_SUCCESS);	
}

int get_min(){
	int min = count[0];
	int i ;
	for(i=1; i<NUM_THREAD; i++){
		if( min > count[i]) min = count[i];
	}
	return min;
}

void * thread_function(void * arg){
	int my_num = *(int *)arg;
	struct tm *t;
	int r;
	time_t _time;
	srand(time(NULL));
	//세마포를 이용해서 쓰래드 동기화
	//나의 값이 최소값과 같으면 값출력 아니면 세마포 넘김
	while(1){	
		sem_wait(&bin_sem);
		if(count[my_num] == get_min()){
			r = rand()%10;
			_time = time(NULL);
			t = localtime(&_time);
			printf("thread_num : %d  time : %d년%d월%d일 %d시 %d분 %d초   call count = %d\n",my_num+1,t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec, ++count[my_num]);
			sem_post(&bin_sem);
			sleep(r);
		
		}
		else{
			sem_post(&bin_sem);
			continue;
		}
		if(count[my_num] == NUM_REPEAT) pthread_exit(NULL);
	}	
}
