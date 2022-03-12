# LSP

Linux System Programming 설계과제_1 을 하기위한 약간의 지식들 설명


<br><br>
# scandir함수
- 헤더파일 `dirent.h` 필요
- 설정한경로와 같은 depth의 파일 및 디렉토리 모두 뽑아옴
- return 파일 및 디렉토리 갯수
```c
struct dirent **items;
scandir(".", &items, NULL, alphasort); // items에 파일이름, 길이 등이 담긴다
```

## chdir , getcwd
- `chdir` : change directory의 약자로 현재 작업디렉토리를 변경한다.
- `getcwd` : 현재 작업디렉토리를 가져온다.
```c
int chdir( const char *dirname ); // 인자로 받은 디렉토리로 이동

char *getcwd( char *buffer, size_t size ); // buffer는 작업 디렉토리 문자열을 담을 버퍼, size는 버퍼 크기
```

## dirent 구조체

```c
struct dirent{
	long d_ino; //inode 번호

	off_t d_off; // offset

	unsigned short d_reclen; //d_name 길이

	char d_name[NAME_MAX+1]; //파일 이름
};
```

## \#include <sys/stat.h>

**1. stat 구조체**

```c
struct stat statbuf;
```
  - stat구조체의 -> st_mode가 S_ISREG or S_ISDIR or ⋯⋯

**2. stat 함수**
```c
stat([filename], [stat구조체]);
```

- S_ISREG – 정규 파일인지 판별

- S_ISDIR – 디렉토리 파일인지 판별

- S_ISCHR – 문자 장치 파일인지 판별

- S_ISBLK – 블록 장치 파일인지 판별

- S_ISFIFO – FIFO 파일인지 판별
