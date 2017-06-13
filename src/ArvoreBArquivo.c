#include "ArvoreBArquivo.h"
void ArvoreComArquivo_Inicializa(TipoPaginaComArquivo **pagina,string filename){
	int i;
	(*pagina) = (TipoPaginaComArquivo*)malloc(sizeof(TipoPaginaComArquivo));
	(*pagina)->filename = filename;
	(*pagina)->arquivo = fopen((*pagina)->filename,"r+b");
	(*pagina)->tamanho_atual = 0;
	for (i = 0; i < MM; i++) {
		(*pagina)->filhos[i] = NULL;
		InicializaRegistro((*pagina)->registros + i);
	}
	(*pagina)->filhos[i] = NULL;

}
void ArvoreComArquivo_Finaliza(TipoPaginaComArquivo **pagina){
	int i;
	free((*pagina)->filename);
	fclose((*pagina)->arquivo);
	(*pagina)->tamanho_atual = 0;
	for (i = 0; i < MM; i++){
		if((*pagina)->filhos[i] != NULL) ArvoreComArquivo_Finaliza(&(*pagina)->filhos[i]);
		//FinalizaRegistro((*pagina)->registros + i); Registro é estatico, quem cuida é o sistema qnd dou free na pagina
	}
	if((*pagina)->filhos[i] != NULL) ArvoreComArquivo_Finaliza(&(*pagina)->filhos[i]);
	free(*pagina);
}
void AbrirArquivos(TipoPaginaComArquivo *PaginaMae, TipoPaginaComArquivo *Pagina){
}
void FecharArquivos(TipoPaginaComArquivo *Ap){
	/*
	 * Fechar o arquivo da pagina
	 * dar free nos ponteiros
	 * e deletar pagina
	 */

}
void ArvoreComArquivo_Pesquisa(TipoRegistro *x, TipoPaginaComArquivo *Ap){
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
	    //TODO:Abrir Arquivos da pagina filha/Inicializar Pagina Filha
        ArvoreComArquivo_Pesquisa(x, Ap->filhos[i-1]);
	    //TODO:Fechar Arquivos da pagina filha/Desalocar Pagina Filha
    }
    else{
	    //TODO:Abrir Arquivos da pagina filha/Inicializar Pagina Filha
	ArvoreComArquivo_Pesquisa(x, Ap->filhos[i]);
	    //TODO:Fechar Arquivos da pagina filha/Desalocar Pagina Filha
    }
}
