#ifndef ARVOREBARQUIVO_H_INCLUDED
#define ARVOREBARQUIVO_H_INCLUDED
#define MM 80
#include <stdio.h>
#include <string.h>
#include "arvB.h"
typedef struct TipoPaginaComArquivo{
    FILE *arquivo;
    short tamanho_atual;
    TipoRegistro registros[MM];
    TipoPaginaComArquivo* filhos[MM + 1];
} TipoPaginaComArquivo;
typedef struct{
	int ID;
	char *nome;
} Registro;
typedef struct _btree{
	struct _btree* Filhas[MM+1];
	Registro regs[MM];
} BTree;
void ArvoreComArquivo_Inicializa(TipoPaginaComArquivo* *Dicionario);
void ArvoreComArquivo_Pesquisa(TipoRegistro *x, TipoPaginaComArquivo* Ap);
void ArvoreComArquivo_InsereNaPagina(TipoPaginaComArquivo* Ap,TipoRegistro Reg, TipoPaginaComArquivo* ApDir);
void ArvoreComArquivo_Ins(TipoRegistro Reg, TipoPaginaComArquivo* Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoPaginaComArquivo* *ApRetorno);
void ArvoreComArquivo_Insere(TipoRegistro Reg, TipoPaginaComArquivo* *Ap);
void ArvoreComArquivo_Reconstitui(TipoPaginaComArquivo* ApPag, TipoPaginaComArquivo* ApPai,int PosPai, short *Diminuiu);
void ArvoreComArquivo_Antecessor(TipoPaginaComArquivo* Ap, int Ind, TipoPaginaComArquivo* ApPai, short *Diminuiu);
void ArvoreComArquivo_Ret(TipoChave Ch, TipoPaginaComArquivo* *Ap, short *Diminuiu);
void ArvoreComArquivo_Retira(TipoChave Ch, TipoPaginaComArquivo* *Ap);
void ArvoreComArquivo_ImprimeI(TipoPaginaComArquivo* p, int nivel);
void ArvoreComArquivo_Imprime(TipoPaginaComArquivo* p);


#endif
