#include <stdio.h>
#include <stdlib.h>

int main(){
	char *fname = "ssu_test.txt";
	FILE *fp;

	if((fp=fopen(fname, "r")) == NULL){
		fprintf(stderr, "fopen error for %s", fname);
		exit(1);
	}
	else{
		printf("Sucess!!\n");
		printf("Opening \"%s\" in \"r\" mode!\n", fname);
	}

	fclose(fp);
	exit(0);
	
}
