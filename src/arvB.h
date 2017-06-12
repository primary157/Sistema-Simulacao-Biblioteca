#include <stdlib.h>
#include <stdio.h>
#define M 2 // 2, 20 e 40. 
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1
typedef struct {
	char *nome_do_livro;
	char *nome_do_autor;
	unsigned int numero_de_exemplares;
}Data;
typedef long TipoChave;
typedef struct TipoRegistro 
{
    TipoChave Chave;
    Data information;
    
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina 
{
    short n;
    TipoRegistro r[MM];
    TipoApontador p[MM + 1];
} TipoPagina;
void InicializaRegistro(TipoRegistro *reg);
void InicializaArvore(TipoApontador *Dicionario);
void Pesquisa(TipoRegistro *x, TipoApontador Ap);
void InsereNaPagina(TipoApontador Ap,TipoRegistro Reg, TipoApontador ApDir);
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno);
void Insere(TipoRegistro Reg, TipoApontador *Ap);
void Reconstitui(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu);
void Antecessor(TipoApontador Ap, int Ind, TipoApontador ApPai, short *Diminuiu);
void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu);
void Retira(TipoChave Ch, TipoApontador *Ap);
void ImprimeI(TipoApontador p, int nivel);
void Imprime(TipoApontador p);
void TestaI(TipoApontador p, int pai, short direita);
void Testa(TipoApontador p);
