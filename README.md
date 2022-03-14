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

struct stat {
     dev_t          st_dev;        /*ID of device containing file */

     ino_t          st_ino;        /*inode number*/

     mode_t         st_mode;       /*protection*/

     nlink_t        st_nlink;      /*number of hard links*/

     uid_t          st_uid;        /*user ID of owner*/

     gid_t          st_gid;        /*group ID of owner*/

     dev_t          st_rdev;       /*device ID (if special file)*/

     off_t          st_size;       /*total size, in byte*/

     blksize_t      st_blksize;    /*blocksize for file system I/O*/

     blkcnt_t       st_blocks;     /*number of 512B blocks allocated*/

     time_t;        st_atime;      /*time of last access*/

     time_t;        st_mtime;      /*time of last modification*/

     time_t         st_xtime;      /*time of last status change*/
};
```
- **핵심**: stat구조체를 이용하여 파일인지 디렉토리인지 파악할 수 있다.
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
