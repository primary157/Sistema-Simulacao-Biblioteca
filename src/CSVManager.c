#include "CSVManager.h"
int openFile(FILE **fptr, string fname){
	return (((*fptr) = fopen(fname,"rb+")) != NULL);
}
int getNextMatch(FILE *fptr,string *match){
	char buffer[512];
	char c;
	int i = 0;
	while((c = fgetc(fptr)) != ';'){	//Procura quebra de Match
		if(c == '\n' || c == '\0'){	//Se a leitura comeca ou com \n ou com \0 eh porque acabaram os matches nessa linha =========> Talvez seja melhor trocar c == '\0' por feof(fptr)
			return 0;		//Sinaliza fim de linha e que nao há match lido
		}
		buffer[i] = c;			//concatena caracter diferente de ';' lido na string buffer
		i++;
	}
	(*match) = (string)malloc(strlen(buffer)*sizeof(char));	//Armazena espaco exato para caber o texto do buffer no match
	strcpy(*match,buffer);					//Copia valor de buffer para match
	return 1;
}
void getNextLine(FILE *fptr, stringArray *matches){
	string buffer[512];
	int i = 0;
	char c;
	while((c = fgetc(fptr)) != '\n'){}
	while(getNextMatch(fptr,&buffer[i])) i++;
	(*matches) = (stringArray)malloc(i*sizeof(string));
	while(i >= 0){
		(*matches)[i] = buffer[i];
		i--;
	}
}
void getRemainingMatches(FILE *fptr, linesOfStringArrays *linesOfMatches){
	int i = 0, j = 0;
	stringArray buffer[512];
	while(getNextMatch(fptr,&buffer[i][j])) j++;
	i++;
	while(!feof(fptr)){
		getNextLine(fptr,&buffer[i]);
		i++;
	}
	(*linesOfMatches) = (linesOfStringArrays)malloc(i*sizeof(stringArray));

	while(i >= 0){
		(*linesOfMatches)[i] = buffer[i];
		i--;
	}
}

void getAllMatches(FILE *fptr, linesOfStringArrays *matches){
	rewind(fptr);
	getRemainingMatches(fptr,matches);
}
long findMatch(FILE *fptr, string match){
	string cmp;
	long pos = -1;
	short achou = 0;
	while(!feof(fptr) && !achou){
		while(getNextMatch(fptr,&cmp)) {
			if(cmp[0] == match[0] && !strcmp(cmp,match)){
				achou = 1;
				break;			//Força fim de iteração
			}
			else{
				pos = (long)ftell(fptr);	//guarda posição do ultimo ';' antes da palavra
			}
		}
	}
	return pos;
}
