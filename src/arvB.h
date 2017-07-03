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
 * @brief Função responsável por Pesquisar registro em uma arvore
 *
 * @param x ponteiro para registro a receber endereço de registro procurado
 *
 * @param Ap Arvore em que se esta pesquisando
 *
 * Essa função irá:
 *
 * 1. Procurar um registro na arvore
 * 2. Atribuir ao ponteiro x o endereço do registro encontrado
 */
void Pesquisa(TipoRegistro *x, TipoApontador Ap);
/**
 * @brief Função responsável por inserir um registro à pagina
 *
 * @param Ap Ponteiro para a Página atual
 * 
 * @param Reg Registro a ser inserido
 * 
 * @param ApDir Ponteiro para a pagina filha à direita do registro a ser inserido
 *
 * Essa função irá:
 *
 * 1. Encontrar posição interna para se inserir Reg
 * 2. Conferir se há espaço para efetuar a inserção
 *   1.Se tiver espaço, inserir
 *   2.Se não tiver espaço, fazer split 
 */
void InsereNaPagina(TipoApontador Ap,TipoRegistro Reg, TipoApontador ApDir);
/**
 * @brief Função responsável por Inserir registro a uma arvore B encapsulada
 *
 * @param Reg registro a ser inserido na arvore
 *
 * @param Ap Arvore em que se esta inserindo
 *
 * @param Cresceu flag usada para marcar quando a arvore cresce na altura
 *
 * @param RegRetorno quando a arvore cresce na altura, essa variavel referencia o registro pertencente a raiz
 *
 * @param ApRetorno quando a arvore cresce na altura, essa variavel referencia a pagina filha da raiz
 *
 * Essa função irá:
 *
 * 1. Encontrar a posição a ser inserido o registrador
 * 2. Inserir o Registrador
 */
void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno);
/**
 * @brief Função responsável por Inserir registro a uma arvore B que encapsula Ins
 *
 * @param Reg registro a ser inserido na arvore
 *
 * @param Ap Arvore em que se esta inserindo
 *
 * Essa função encapsula a função Ins reduzindo os numeros de parametros passados.
 */
void Insere(TipoRegistro Reg, TipoApontador *Ap);
/**
 * @brief Função responsável por corrigir quebra das regras da Arvore B
 *
 * @param ApPag Pagina a ser tratada
 *
 * @param ApPai Pagina pai da pagina a ser tratada
 *
 * @param PosPai Indice da pagina a ser tratada no vetor de filhos da pagina pai
 *
 * @param Diminuiu flag ativada quando há uma diminuição na altura da arvore
 *
 * Essa função irá:
 *
 * 1. Confere se ApPag é ultimo filho de ApPai
 * 	1. Se é o último filho considera Pagina irma como sendo a da esquerda (anterior no vetor de paginas de ApPai)
 * 	2. Caso Contrário considera Pagina irma como sendo a da direita (proxima no vetor de paginas de ApPai)
 * 2. Confere se pagina irma possui algum registro para doar
 * 	1. Se pagina irma possui registro para doar, este registro é transferido para ApPai e o registro de ApPai que delimitava os valores entre as Paginas irmas é trazido para a ApPag
 * 	2. Caso Contrario é executado o merge, onde ambas as paginas irmas sao concatenadas e recebem o registro de ApPai que delimitava os valores entre elas
 */
void Reconstitui(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu);
/**
 * @brief Função responsável por encontrar registro antecessor ao Ap
 *
 * @param Ap pagina onde sera inserido o antecessor
 *
 * @param Ind indice da pagina Ap no vetor de filhos de ApPai
 *
 * @param ApPai Pagina origem do antecessor
 *
 * @param Diminuiu flag ativada quando há uma diminuição na altura da arvore
 *
 * Essa função irá:
 *
 * 1. Percorrer a arvore pelas paginas à esquerda até encontrar o nó folha
 * 2. Capturar o maior registro do nó folha como sendo o antecessor
 */
void Antecessor(TipoApontador Ap, int Ind, TipoApontador ApPai, short *Diminuiu);
/**
 * @brief Função responsável por retirar registro da arvore encapsulada
 *
 * @param Ch Chave do Registro a ser removido
 *
 * @param Ap Arvore em que se esta removendo
 *
 * @param Diminuiu flag para alertar redução na altura da arvore
 *
 * Essa função irá:
 *
 * 1.Encontrar o registro a ser removido
 * 2.Remove-o, chamando as devidas funções auxiliares para reestruturar a arvore atendendo as regras da Arvore B
 */
void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu);
/**
 * @brief Função responsável por retirar registro da arvore
 *
 * @param Ch Chave do Registro a ser removido
 *
 * @param Ap Arvore em que se esta removendo
 *
 * Essa função encapsula a função Ret reduzindo os numeros de parametros passados.
 */
void Retira(TipoChave Ch, TipoApontador *Ap);
/**
 * @brief Função responsável por Imprimir conteudo da Arvore B
 *
 * @param p Arvore a ser imprimida
 *
 * @param nivel variavel auxiliar para calcular nivel de altura acessado
 *
 * Essa função irá passar por todas as paginas imprimindo seus conteudos
 */
void ImprimeI(TipoApontador p, int nivel);
/**
 * @brief Função responsável por encapsular a função ImprimeI
 *
 * @param p Arvore a ser imprimida
 *
 * Essa função encapsula a função ImprimeI reduzindo os numeros de parametros passados.
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
