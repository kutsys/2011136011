#include <stdio.h>
#include <stdlib.h>
extern char **environ;

int main(){
	int flag = 0;

	/* testevn라는 환경변수에 1234라는 값을 설정하고
	 이미 존재하면 overwrite해준다. 그리고 설정이 완료되었는지를
	 flag를 통해서 확인해준다 */
	flag = setenv( "TEST_ENV" , "1234" , 1);
	if(flag == 0) printf("success\n");
	else printf("failed\n");

	/*setenv로 설정된 환경변수의 값은 응용이 작동할때만 유효하므로
	응용안에서 environ이라는 변수를 이용해서 보여준다
	응용이 끝나고도 유지 하려면 bashrc에 적어주어야 한다.*/
	while(*environ){
		printf("%s\n",*environ++);
	}
	exit(0);
}
