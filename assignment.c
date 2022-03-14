#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <malloc.h>

#define MAX 1024

char **parse(char *);
void help_print();

static int  indent = 0;

char cdir[256];


void myfunc(char *file, struct stat *fstat){

	printf("%d ", fstat->st_size);
	printf("%d ", fstat->st_blocks);	
	printf("%d ", fstat->st_nlink);	
	printf("%d ", fstat->st_uid);	
	printf("%d ", fstat->st_gid);	
	printf("%d ", fstat->st_atime);	
	printf("%d ", fstat->st_ctime);	
	printf("%d ", fstat->st_mtime);	
	printf("%d ", fstat->st_mode);
	if(strcmp(getcwd(cdir,256), "/")){
		printf("%s/%s\n", getcwd(cdir, 256),file);
	}
	else{
		printf("/%s\n",file);
	}
}


void Scandir(char *file, char *wd, void (*func)(char *, struct stat *), int depth)
{
    struct dirent **items;
    int nitems, i;
    // 인자로 받은 디렉토리로 이동한다.
    if (chdir(wd) < 0)
    {
        printf("DIR : %s\n", wd);
        perror("chdir ");
    	return;
    }

    // scandir 함수를 이용해서 <현재 디렉토리>의
    // 모든 파일과 디렉토리의 내용을 가져온다.
    nitems = scandir(".", &items, NULL, alphasort);

    // 디렉토리(파일포함) 항목의 갯수만큼 루프를 돌리며
    // 만약 해당 파일이 디렉토리 일경우
    // Scandir 함수를 재귀 호출한다.
    for (i = 0; i < nitems; i++)
    {
        // 파일 상태를 저장하기 위한 구조체
        struct stat fstat;
        // 현재디렉토리, 이전디렉토리 는 무시한다.
        if ( (!strcmp(items[i]->d_name, ".")) || (!strcmp(items[i]->d_name, "..")) )
        {
            continue;
        }
        

        lstat(items[i]->d_name, &fstat);


	if(!strcmp(items[i]->d_name, file)){
		
		// 함수포인터를 호출한다. 인자로 검색한 파일이름과 속성들을 출력하는 함수이다.
        	func(items[i]->d_name, &fstat);
	
	}

        // 만약 파일이 디렉토리 이라면
        // Scandir 을 재귀 호출한다.
        // 그리고 디렉토리의 depth 레벨을 1 증가 한다.
        if(S_ISDIR(fstat.st_mode))
	{
            // depth만큼만 하부 디렉토리검색을 한다.
            // 0일 경우 깊이에 관계없이 검색한다.
             // if (indent < (depth-1) || (depth == 0))
            
            //	indent ++;
                 Scandir(file, items[i]->d_name, func, depth);
          
        }
    }
    // 디렉토리의 depth 레벨을 1 감소시키고
    // 하위 디렉토리로 이동한다.
    // indent --;
    chdir("..");
}

int main(){
	
	char ter[MAX];
	char** command = NULL;
	struct timeval start, end;
	double diff;
	gettimeofday(&start, NULL);	
	
	while(1){
		printf("20193439> ");
		gets(ter);
		
		if(!strcmp(ter,"")) continue;
		
		command = parse(ter);
			
		if(command == NULL){
			help_print();
		}
		else if(!strcmp(command[0],"quit")){
			gettimeofday(&end, NULL);
			diff = ( end.tv_sec - start.tv_sec ) + (end.tv_usec - start.tv_usec) / 1000000.0;
			printf("Prompt End\n");
			printf("Runtime: %d:%d(sec:usec)", (int)diff, (int)((diff-(int)diff)*1000000.0));
			return 0;
		}
		else if(!strcmp(command[0],"find")){
			Scandir(command[1], command[2], myfunc, 0);
		}
		else{
			help_print();
		}

	}
}


char **parse(char *data){

	int i = 0; // 재할당되는 이중포인터의 갯수
	char** ptr = (char**)malloc(sizeof(char *));


	char *tmp_ptr = strtok(data," "); // 처음 토큰을 넣는다.
	
	if(tmp_ptr == NULL)
		return NULL;

	while(tmp_ptr!=NULL)
	{
		if(i >= 3){
			return NULL; // 어떤 인자든간에 4개의 인자가 들어간다면 NULL 리턴
		}


    		ptr[i++] = tmp_ptr;
     		tmp_ptr = strtok(NULL," ");
		if(!strcmp(ptr[0],"quit") && tmp_ptr!=NULL){ // quit뒤에 다른인자 오는순간 바로 NULL 리턴(2번째)
			return NULL;
		}

		
		if( (ptr = (char**)realloc(ptr, (i+1)*sizeof(char *))) == NULL ){
			fprintf(stderr, "Memory Reallocation Error !!!\n");
			exit(0);
		}
    	}

	free(tmp_ptr);

	return ptr;
}

void help_print(){
			printf("Usage:\n  > find [FILENAME] [PATH]\n");
			printf("     >> [INDEX] [OPTION ... ]\n");
			printf("  > help\n");
			printf("  > exit\n\n");
			printf("  [OPTION ... ]\n   q : report only when files differ\n   s : report when two files are the same\n");
			printf("   i : ignore case differences in file contents\n   r : recursively compare any subdirectories found\n\n");
}
