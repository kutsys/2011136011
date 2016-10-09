#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir,int depth){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	//매개변수로 받아온 디렉토리를 열어서 DIR포인터 변수 dp에 저장	
	if((dp = opendir(dir)) == NULL){
		fprintf(stderr,"cannot open dirctory: %s\n", dir);
		return;
	}
	
	chdir(dir);
	while((entry=readdir(dp)) != NULL) {
		lstat(entry->d_name, &statbuf);

		
		if(S_ISDIR(statbuf.st_mode)) {
		//디렉토리가 존재하는지 검사한후 없으면 pass
			if(strcmp(".",entry->d_name) ==0 ||
			   strcmp("..",entry->d_name) ==0) continue;
	
			//만약 이름이 .으로 시작한다면 pass	
			if(entry->d_name[0]=='.') continue;	
			//그게 아니면 이름을 출력해주고 printdir재귀 호출
			printf("%*s%s/\n",depth,"",entry->d_name);
			printdir(entry->d_name,depth+4);
		}else {
			//만약 이름이 .으로 시작한다면 pass
			if(entry->d_name[0] == '.') continue;
			printf("%*s%s\n",depth,"",entry->d_name);
		}	
	}
	chdir("..");
	closedir(dp);
}

int main(){
	printf("Directory scan of /home:\n");
	//현재 디렉토리정보를 출력하기 위해서 첫번째 매개변수로 .	
	printdir(".",0);
	printf("done.\n");
	exit(0);
}

