#include "ArvoreBArquivo.h"
void decode(char *c, char **text){
	int i = 0,j = 0,k = 0;
	while (c[i] != '\0') {
		if(c[i] == ';'){
			k++;
			j = 0;
		}
		else{
			text[k][j++] = c[i];
		}
		i++;
	}
}
void loadBTree(BTree *t){
	FILE *f;
	char buffer[128];
	char *texts[10][20];
	int i,j,k; 
	short EndOfLine;
	if((f = fopen("w","tudo.csv"))==NULL){
		printf("Failed...");
		return;
	}
	for (i = 0; !feof(f); i++) {
		EndOfLine = 0;
		for (j = 0; EndOfLine; j++) {
			for (k = 0;; k++) {
				buffer[k] = fgetc(f);
				if(buffer[k] == '\n'){
					buffer[k] = '\0';
					strcpy(texts[i][j],buffer);
					EndOfLine = 1;
					break;
				}
				else if(buffer[k] == ';'){
					buffer[k] = '\0';
					strcpy(texts[i][j],buffer);
					break;
				}
			}
		}

	}
	//TODO:Interpretar buffer
	

	//TODO:Construir Arvore B
}
