#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <malloc.h>
#include <time.h>

#define MAX 1024

char **parse(char *);
void help_print();

static int  idx = 0;

char cdir[256];

char buf1[1024];// command[1]
struct stat fstat_1;// command[1] stat

void myfunc(char *file, struct stat *fstat){
	
    	struct tm *tm;
	char buf[200];
	
	printf("%-6d", idx++); // Index
	printf("%-7d ", fstat->st_size); // Size

    printf( (S_ISDIR(fstat->st_mode)) ? "d" : "-");
    printf( (fstat->st_mode & S_IRUSR) ? "r" : "-");
    printf( (fstat->st_mode & S_IWUSR) ? "w" : "-");
    printf( (fstat->st_mode & S_IXUSR) ? "x" : "-");
    printf( (fstat->st_mode & S_IRGRP) ? "r" : "-");
    printf( (fstat->st_mode & S_IWGRP) ? "w" : "-");
    printf( (fstat->st_mode & S_IXGRP) ? "x" : "-");
    printf( (fstat->st_mode & S_IROTH) ? "r" : "-");
    printf( (fstat->st_mode & S_IWOTH) ? "w" : "-");
    printf( (fstat->st_mode & S_IXOTH) ? "x" : "-");

    	printf("  %-7d ", fstat->st_blocks);
	printf("%-7d ", fstat->st_nlink);	
	printf("%-7d ", fstat->st_uid);	
	printf("%-7d ", fstat->st_gid);

	
    	tm = localtime(&fstat->st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm); /* format time days.month.year hour:minute:seconds */
   	printf("%s ", buf);	
	
	
    	tm = localtime(&fstat->st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm);
   	printf("%s ", buf);	
	

    	tm = localtime(&fstat->st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm);
   	printf("%s ", buf);	

	
	if(strcmp(getcwd(cdir,256), "/")){
		printf("%s/%s\n", getcwd(cdir, 256),file);
	}
	else{
		printf("/%s\n",file);
	}
}


void myfunc2(char *file){
	
    	struct tm *tm;
	char buf[200];
	
	printf("Index Size    Mode        Blocks  Links   UID     GID Access Change Modify Path \n");
        
	lstat(file, &fstat_1);

	printf("%-6d", idx++);	
	printf("%-7d ", fstat_1.st_size);

    printf( (S_ISDIR(fstat_1.st_mode)) ? "d" : "-");
    printf( (fstat_1.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fstat_1.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fstat_1.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fstat_1.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fstat_1.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fstat_1.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fstat_1.st_mode & S_IROTH) ? "r" : "-");
    printf( (fstat_1.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fstat_1.st_mode & S_IXOTH) ? "x" : "-");	
	
    	printf("  %-7d ", fstat_1.st_blocks);	
	printf("%-7d ", fstat_1.st_nlink);	
	printf("%-7d ", fstat_1.st_uid);	
	printf("%-7d ", fstat_1.st_gid);

		
    	tm = localtime(&fstat_1.st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm); /* format time days.month.year hour:minute:seconds */
   	printf("%s ", buf);	
	
	
    	tm = localtime(&fstat_1.st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm);
   	printf("%s ", buf);	
	

    	tm = localtime(&fstat_1.st_atime); /* convert time_t to broken-down time representation */
	
    	strftime(buf, sizeof(buf), "%y-%m-%d %H:%M", tm);
   	printf("%s ", buf);	

	printf("%s\n",file);
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
        if(S_ISDIR(fstat.st_mode))
	{
            
                 Scandir(file, items[i]->d_name, func, depth); // 하위로 한칸 이동
          
        }
    }
    // 하위 디렉토리로 이동한다.
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
			char buf2[1024];
		        char cdir[256];
			char *ptr;
			getcwd(cdir, 256); // Scandir이 끝나면 '/'로 이동되므로, cdir미리 저장 => 다시 원래 디렉토리로 이동(getcwd+chdir)	
			
			if(realpath(command[1], buf1) == NULL){ // command[1] 절대경로로 변환 
				perror(buf1);
				printf("\n");
				continue;
			}

   			ptr = strrchr(buf1, '/');     // "/"으로 시작하는 문자열 검색, 포인터 반환 (command[1]의 절대경로빼고 파일이름만 반환받기 위함)
    			ptr+=1;

			if(realpath(command[2], buf2) == NULL){ // command[2] 절대경로 있는지 검사
				perror(buf2);
				printf("\n");
				continue;
			}; 
			myfunc2(buf1);
			Scandir(ptr, command[2], myfunc, 0);
			chdir(cdir); // Scandir끝난후 원래 디렉토리로 이동
			idx = 0;
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
	
	if(tmp_ptr == NULL) // spacebar만 있을경우 NULL을 리턴
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
