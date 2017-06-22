/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao das funções do TAD Arvore B implementado por Nivio Ziviani
 * 
 *
 * @details Arquivo de Implementacao do TAD Arvore B implementado por Nivio Ziviani em seu livro: 
 * "Projeto de algoritmos em C/Pascal"
 * 
 */
#ifndef ARVB_H_INCLUDED
#define ARVB_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define M 2 // 2, 20 e 40. 
#define MM  (M * 2)
#define FALSE 0
#define TRUE  1

/**
 * @brief Tipo que armazena dados que não sejam a chave no registro da Arvore B
 *
 * Este tipo apresenta os dados do registro que não são usados na indexação da Estrutura de Dados
 */
typedef struct {
	char nome_do_livro[40];
	char nome_do_autor[20];
	unsigned int numero_de_exemplares;
}Data;

/**
 * @brief Tipo Chave usado na indexação do TAD Arvore B
 */
typedef long TipoChave;
/**
 * @brief Tipo contido nas páginas da arvore B
 *
 * Esse Tipo é responsável por armazenar os dados individuais de cada registro armazenado em uma
 *  árvore B
 */
typedef struct TipoRegistro 
{
    TipoChave Chave;
    Data information;
    
} TipoRegistro;

/**
 * @brief Definição do TipoApontador como sendo um ponteiro para struct TipoPagina
 */
typedef struct TipoPagina* TipoApontador;

/**
 * @brief Principal TAD da Arvore B
 *
 * Esse TAD é o diferencial da Arvore B, ele contem MM registros e MM+1 ponteiros para
 * Paginas Filhas
 */
typedef struct TipoPagina 
{
    short tamanho_atual;			///< numero de registros contidos na pagina
    TipoRegistro registros[MM];		///< Vetor de Registros armazenados na Pagina
    TipoApontador filhos[MM + 1];	///< Ponteiro para Paginas Filhas
} TipoPagina;
/**
 * @brief Função responsável por Inicializar um Registro
 *
 * @param reg Ponteiro para Registro que será inicializado
 *
 * Essa função irá atribuir os valores iniciais a um registro
 *
 */
void InicializaRegistro(TipoRegistro *reg);
/**
 * @brief Função responsável por Inicializar página da Arvore B e atribuir os valores iniciais padrões a esta
 *
 * @param pagina Ponteiro para ponteiro de pagina a ser Inicializada 

 */
void InicializaArvore(TipoApontador *pagina);
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
void Pesquisa(TipoRegistro *x, TipoApontador Ap);
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
void InsereNaPagina(TipoApontador Ap,TipoRegistro Reg, TipoApontador ApDir);
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
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno);
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
void Insere(TipoRegistro Reg, TipoApontador *Ap);
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
void Reconstitui(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu);
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
void Antecessor(TipoApontador Ap, int Ind, TipoApontador ApPai, short *Diminuiu);
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
void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu);
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
void Retira(TipoChave Ch, TipoApontador *Ap);
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
void ImprimeI(TipoApontador p, int nivel);
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
void Imprime(TipoApontador p);
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
void TestaI(TipoApontador p, int pai, short direita);
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
void Testa(TipoApontador p);
#endif
