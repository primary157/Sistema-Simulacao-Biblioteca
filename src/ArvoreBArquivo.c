#include "ArvoreBArquivo.h"
void ArvoreComArquivo_Inicializa(TipoPaginaComArquivo **pagina){
	int i;
	(*pagina) = (TipoPaginaComArquivo*)malloc(sizeof(TipoPaginaComArquivo));
	(*pagina)->tamanho_atual = 0;
	for (i = 0; i < MM; i++) {
		(*pagina)->filhos[i] = NULL;
		InicializaRegistro((*pagina)->registros + i);	///<Falta ler o arquivo (*pagina)->arquivo indice individual da pagina

	}
	(*pagina)->filhos[i] = NULL;
}
void ArvoreComArquivo_Finaliza(TipoPaginaComArquivo **pagina){
	int i;
	for (i = 0; i <= MM; i++){
		if((*pagina)->filhos[i] != NULL) ArvoreComArquivo_Finaliza(&(*pagina)->filhos[i]);
	}
	free(*pagina);
}

void LerArquivo(TipoPaginaComArquivo *PaginaMae, int i, FILE **fptr){
	int j;
	TipoPaginaComArquivo **Pagina = &PaginaMae->filhos[i];
	if(fptr == NULL)
		return;
	ArvoreComArquivo_Inicializa(Pagina);
	
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
void FecharArquivos(TipoPaginaComArquivo **Ap){
	free((*Ap));
	(*Ap) = NULL;
}
void ArvoreComArquivo_Pesquisa(TipoRegistro *x, TipoPaginaComArquivo *Ap){
    FILE *fptr = globalFile;
    long i = 1;
    if (Ap == NULL) {
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->tamanho_atual && x->Chave > Ap->registros[i-1].Chave) i++;
    if (x->Chave == Ap->registros[i-1].Chave) {
        *x = Ap->registros[i-1];
        return;
    }
    if (x->Chave < Ap->registros[i-1].Chave){
	LerArquivo(Ap, i-1,&fptr);
        ArvoreComArquivo_Pesquisa(x, Ap->filhos[i-1]);
	FecharArquivos(&Ap->filhos[i-1]);
	return;
    }
    LerArquivo(Ap,i,&fptr);
    ArvoreComArquivo_Pesquisa(x, Ap->filhos[i]);
    FecharArquivos(&Ap->filhos[i]);
}
