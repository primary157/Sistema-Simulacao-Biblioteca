#include "ArvoreBArquivo.h"

void LerArquivo(TipoPagina *PaginaMae, int i, FILE **fptr){
	int j;
	TipoPagina **Pagina = &PaginaMae->filhos[i];
	if(fptr == NULL)
		return;
	InicializaArvore(Pagina);
	
	//PaginaMae->filhos[i] = *Pagina;
	//fseek(*fptr,offset,SEEK_SET);	COMENTADO POIS PARAMETRO JA VEM NA POSICAO NECESSARIA
	fread(&(*Pagina)->tamanho_atual,sizeof(short),1,*fptr);
	for (j = 0; j < (*Pagina)->tamanho_atual; j++) {
		fread(&(*Pagina)->registros[j].Chave,sizeof(long),1,*fptr);
		fread((*Pagina)->registros[j].information.nome_do_livro,sizeof(char),40,*fptr);
		fread((*Pagina)->registros[j].information.nome_do_autor,sizeof(char),20,*fptr);
		fread(&(*Pagina)->registros[j].information.numero_de_exemplares,sizeof(unsigned int),1,*fptr);
	}
	//TODO: chamar Insere para o nó
	//TODO: chamar recursivamente LerArquivo para os nós filhos até alcançar as folhas
	

}
