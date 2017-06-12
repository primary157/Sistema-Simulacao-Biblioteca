#include "ArvoreBArquivo.h"
void ArvoreComArquivo_Inicializa(TipoPaginaComArquivo **pagina){
	int i;
	(*pagina) = (TipoPaginaComArquivo*)malloc(sizeof(TipoPaginaComArquivo));
	(*pagina)->tamanho_atual = 0;
	for (i = 0; i < MM; i++) {
		(*pagina)->filhos[i] = NULL;
		InicializaRegistro((*pagina)->registros + i);
	}
	(*pagina)->filhos[i] = NULL;
	(*pagina)->tamanho_atual = 0;

}
