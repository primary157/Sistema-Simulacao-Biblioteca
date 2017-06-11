#include "CSVManager.h"
int openFile(FILE **fptr, string fname){
	return (((*fptr) = fopen(fname,"rb+")) != NULL);
}
FILE* findPosAndStoreNextText(FILE *fptr,int line, string *remainingText){
	char c;
	size_t cur_position, eof_position;
	int i;
	if(line == CURRENT_LINE){
		while((c = fgetc(fptr)) != '\n'){}
	}
	else if(line > 0){
		rewind(fptr);
		for (i = 0; i < line; i++) {
			while((c = fgetc(fptr)) != '\n'){}
		}
	}
	else{
		fseek(fptr, 0, SEEK_END);
		for (i = 0; i > (line+1); i--) {	//Se line == -1 entao encontrar fim da ultima linha, ou seja, fim do arquivo. Se line < -1 entao encontrar (line+1) \n's 
			while((c = fgetc(fptr)) != '\n') fseek(fptr,-2,SEEK_CUR);
		}
	}
	//fseek(fptr,-1,SEEK_CUR); COMENTADO PARA ATENDER TANTO A addMatchToLine QUANTO A changeLineMatches	//Voltar ao ponto de quebra de linha

	cur_position = ftell(fptr);	//Salva posicao atual
	fseek(fptr,0,SEEK_END);		//Vai ate o fim do arquivo
	eof_position = ftell(fptr);	//Le tamanho do arquivo
	fseek(fptr,cur_position,SEEK_SET);	//Volta a posicao salva

	(*remainingText) = (string)malloc((eof_position-cur_position)*sizeof(char));
	fread((*remainingText),sizeof(char),eof_position-cur_position,fptr);
	fseek(fptr,cur_position,SEEK_SET);
	return fptr;

}
void addMatchToLine(FILE *fptr,string match, int line){
	string remainingText;
	fptr = findPosAndStoreNextText(fptr,line, &remainingText);
	fseek(fptr,-1,SEEK_CUR);	//Necessario porque removi esse comando da funcao findPosAndStoreNextText
	fputs(match,fptr);
	fputc('\n',fptr);
	fputs(remainingText,fptr);
	free(remainingText);
}
void changeLineMatches(FILE *fptr,stringArray matches, int n_matches, int line){
	char c;
	string remainingText;
	int i;
	if(line == CURRENT_LINE){
		while((c = fgetc(fptr)) != '\n' && ftell(fptr) != 0) fseek(fptr,-2,SEEK_CUR); // Encontrar quebra de linha e ultrapassa-lo
	}
	else if(line > 0){
		rewind(fptr);
		for (i = 0; i < (line-1); i++) {
			while((c = fgetc(fptr)) != '\n'){} // Encontrar quebra de linha e ultrapassa-lo
		}
	}
	else{
		fseek(fptr, -2, SEEK_END);
		for (i = 0; i > line; i--) {
			while((c = fgetc(fptr)) != '\n') fseek(fptr,-2,SEEK_CUR);
		}
	}
	findPosAndStoreNextText(fptr,CURRENT_LINE,&remainingText);	//Ja esta na linha certa por isso passar CURRENT_LINE
	for (i = 0; i < n_matches; i++) {
		fputs(matches[i],fptr);
		fputc(';',fptr);
	}
	fputc('\n',fptr);
	fputs(remainingText,fptr);
	free(remainingText);
}
int getNextMatch(FILE *fptr,string *match){
	char buffer[512];
	char c;
	int i = 0;
	while((c = fgetc(fptr)) != ';'){	//Procura quebra de Match
		if(c == '\n' || c == '\0'){	//Se a leitura comeca ou com \n ou com \0 eh porque acabaram os matches nessa linha =========> Talvez seja melhor trocar c == '\0' por feof(fptr)
			fseek(fptr,-1,SEEK_CUR);	//volta o ponteiro fptr para a posicao de quebra de linha ou de fim de arquivo
			return 0;	
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
