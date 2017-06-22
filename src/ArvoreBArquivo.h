/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao das funções do TAD modificado de Arvore B que faz uso de indexação 
 * por arquivos para leitura e escrita
 *
 * @details Nesse arquivo sobrescrevemos algumas funções básicas da implementação de Árvore B do Nivio Ziviani, 
 * dando a essa estrutura de dados a capacidade de gerenciar seus dados em arquivos de texto estruturados
 */

#ifndef ARVOREBARQUIVO_H_INCLUDED
#define ARVOREBARQUIVO_H_INCLUDED
#define MM 80
#define filename "tree.dat"
#include <stdio.h>
#include <string.h>
#include "arvB.h"
#include "CSVManager.h"

/**
 * @brief Ponteiro para arquivo de indexação geral da arvore
 */
FILE *globalFile = fopen(filename,"r+");


/**
 * @brief Tipo Responsavel por armazenar dados na Arvore B
 *
 * Esse Tipo é responsável por armazenar dados na Arvore B
 */
typedef struct TipoPaginaComArquivo{
    short tamanho_atual;
    TipoRegistro registros[MM];
    TipoPaginaComArquivo* filhos[MM + 1];
} TipoPaginaComArquivo;
/**
 * @brief Função responsável por Inicializar página da Arvore B com Arquivo
 *
 * @param pagina Ponteiro para ponteiro de pagina que sera responsavel por amazenar pagina alocada
 * @param filename String do nome do arquivo a ser lido para popular a Pagina
 *
 * Essa função irá:
 *
 * 1. Alocar espaço para a pagina
 * 2. Abrir arquivo
 * 3. Inicializar os registros de acordo com o arquivo
 */
void ArvoreComArquivo_Inicializa(TipoPaginaComArquivo **Dicionario);

/**
 * @brief Função responsável por Finalizar página da Arvore B com Arquivo
 *
 * @param pagina Ponteiro para ponteiro de pagina que armazena Pagina a ser liberada
 *
 * Essa função irá:
 *
 * 1. Fechar arquivo
 * 2. Desalocar espaço para a pagina
 */
void ArvoreComArquivo_Finaliza(TipoPaginaComArquivo **pagina);

/**
 * @brief Função responsável por Demandar a inicialização de uma pagina e chamar as funções necessárias para isso
 *
 * @param PaginaMae Ponteiro para Pagina com arquivo referente à Pagina Mae do No que sera aberto
 * @param Pagina Ponteiro para Pagina com arquivo referente ao No que sera aberto
 * @param i Indice do Registro da PaginaMae que tem como filho o parametro Pagina
 *
 * Essa função irá:
 *
 * 1. Encontrar no tudo.csv o arquivo da pagina de nome fname (nome da pagina pai)
 * 2. Encontrar no arquivo de nome fname o indice referente a pagina a ser aberta
 * 3. Abrir arquivo, atribuir valores as variaveis da pagina
 */
void AbrirArquivos(TipoPaginaComArquivo *PaginaMae, TipoPaginaComArquivo *Pagina, int i);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Pesquisa(TipoRegistro *x, TipoPaginaComArquivo* Ap);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_InsereNaPagina(TipoPaginaComArquivo* Ap,TipoRegistro Reg, TipoPaginaComArquivo* ApDir);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Ins(TipoRegistro Reg, TipoPaginaComArquivo* Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoPaginaComArquivo* *ApRetorno);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Insere(TipoRegistro Reg, TipoPaginaComArquivo* *Ap);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Reconstitui(TipoPaginaComArquivo* ApPag, TipoPaginaComArquivo* ApPai,int PosPai, short *Diminuiu);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Antecessor(TipoPaginaComArquivo* Ap, int Ind, TipoPaginaComArquivo* ApPai, short *Diminuiu);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Ret(TipoChave Ch, TipoPaginaComArquivo* *Ap, short *Diminuiu);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Retira(TipoChave Ch, TipoPaginaComArquivo* *Ap);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_ImprimeI(TipoPaginaComArquivo* p, int nivel);

/**
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
void ArvoreComArquivo_Imprime(TipoPaginaComArquivo* p);


#endif
