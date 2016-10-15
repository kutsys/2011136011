#include <stdio.h>
#include <stdlib.h>

int main(){
	/*getenv를 이용해서 각각의 경로를 하나씩 출력해준다 */
	printf("HOME : %s\n",getenv("HOME"));
	printf("PS1  : %s\n",getenv("PS1"));
	printf("PATH : %s\n",getenv("PATH"));
	printf("LD_LIBRARY_PATH : %s\n",getenv("LD_LIBRARY_PATH"));
	exit(0);
}
