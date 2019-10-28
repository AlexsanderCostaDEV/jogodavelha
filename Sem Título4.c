#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *ff = fopen("inicio.bin", "rb");
	if(ff == NULL){
		printf("Nao foi possivel abrir o arquivo!\n");
		exit(1);
	}
	
	int c;
	
//	fseek(ff, -1*sizeof(c), SEEK_END);
	while(!feof(ff)){
		fread(&c, sizeof(c), 1, ff);
		printf("%d\n\n", c);
	}
	
	
	fclose(ff);
	system("pause");
	return 0;
}
