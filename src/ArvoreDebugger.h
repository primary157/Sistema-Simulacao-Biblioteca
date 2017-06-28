/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "27/06/2017"
 * @brief Arquivo de Implementacao das funções do TAD Arvore B com contagem de acessos a disco
 *
 * @details Nesse arquivo implementamos a função altura e sobrescrevemos algumas funções básicas da implementação de Árvore B do Nivio Ziviani, 
 * dando às suas funções a habilidade de contabilizar os acessos a disco e comparações
 */

#ifndef ARVOREDEBUGGER_H_INCLUDED
#define ARVOREDEBUGGER_H_INCLUDED
#include "arvB.h"
/**
 * @brief Tipo que armazena acumuladores de acessos a disco
 *
 * Este tipo possui um contador de acessos a disco, alem de dois contadores para os diferentes tipos de acesso(leitura e escrita)
 */
typedef struct{
	int escrita;
	int leitura;
	int total;
} AcessosADisco;
/**
 * @brief Tipo que armazena dados capturados pelo debugger
 *
 * Este tipo possui os contadores de acesso a disco e de comparações
 */
typedef struct{
	AcessosADisco num_acessos_a_disco;
	unsigned int comparacoes;
}Debugger;

/**
 * @brief enum que abrange ambos os Tipos de Acesso (Leitura e Escrita)
 *
 * enum que abrange ambos os Tipos de Acesso (Leitura e Escrita), utilizada na função de incrementar acessos a disco
 */
typedef enum{ ACESSO_DE_ESCRITA, ACESSO_DE_LEITURA } TipoDeAcesso;
//Algoritmos internos
/**
 * @brief Função responsável por reiniciar um debugger
 *
 * @param dbg Ponteiro para Debugger a ser reiniciado
 *
 * Essa função irá atribuir os valores iniciais a um Debugger
 *
 */
void resetDebugger(Debugger *dbg);
/**
 * @brief Função responsável por Incrementar o contador de comparações
 *
 * @param dbg Debugger que armazenará contador a ser incrementado
 *
 * Essa Função responsável por Incrementar o contador de comparações
 *
 */
void incComparacoes(Debugger *dbg);
/**
 * @brief Função responsável por Incrementar o contador de acessos a disco
 *
 * @param dbg Debugger que armazenará contadores a serem incrementado
 *
 * @param tipo_de_acesso define qual tipo de acesso sera feito para incrementar contador especifico 
 *
 * Essa Função é responsável por Incrementar o contador total de acessos a disco e o contador especifico do tipo de acesso especificado
 *
 */
void incAcessos_a_disco(TipoDeAcesso tipo_de_acesso,Debugger *dbg);
/**
 * @brief Função responsável por imprimir valores armazenados pelo debugger
 *
 * @param dbg Ponteiro para Debugger a ser imprimidio
 *
 * Essa função irá imprimir valores armazenados em um Debugger
 *
 */
void imprimeDebugger(Debugger *dbg);
//Algoritmos da Arvore B


/**
 * @brief Função recursiva responsável por calcular a altura da Arvore B
 *
 * @param Ap Ponteiro para Arvore B a ter a altura calculada
 *
 * @return altura da arvore Ap
 *
 * Essa função irá calcular a altura da Arvore B seguindo o caminho mais a esquerda da Arvore até o fim(pela Arvore B ser balanceada não faz diferença qual caminho seguir)
 *
 */
int altura(TipoApontador *Ap);
/**
 * @brief Função responsável por Pesquisar registro em uma arvore contando numero de acessos a disco e comparações feitas
 *
 * @param x ponteiro para registro a receber endereço de registro procurado
 *
 * @param Ap Arvore em que se esta pesquisando
 *
 * @param dbg Debugger que armazenará contadores a serem incrementado
 *
 * Essa função irá:
 *
 * 1. Procurar um registro na arvore, contando numero de acessos a disco e numero de comparações feitas
 * 2. Atribuir ao ponteiro x o endereço do registro encontrado
 */
void PesquisaComContagem(TipoRegistro *x, TipoApontador Ap,Debugger *dbg);
/**
 * @brief Função responsável por Inserir registro a uma arvore B encapsulada com contagem de acessos ao disco e comparações
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
 * @param dbg Debugger que armazenará contadores a serem incrementado
 *
 * Essa função irá:
 *
 * 1. Encontrar a posição a ser inserido o registrador, contando numero de acessos de leitura
 * 2. Inserir o Registrador, contando numero de acessos de leitura
 */
void InsComContagem(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno,Debugger *dbg);
/**
 * @brief Função responsável por Inserir registro a uma arvore B com contagem de acessos ao disco e comparações
 *
 * @param Reg registro a ser inserido na arvore
 *
 * @param Ap Arvore em que se esta inserindo
 *
 * @param dbg Debugger que armazenará contadores a serem incrementado
 *
 * Essa função encapsula a função InsComContagem reduzindo os numeros de parametros passados.
 *
 */
void InsereComContagem(TipoRegistro Reg, TipoApontador *Ap,Debugger *dbg);
/**
 * @brief Função responsável por retirar registro da arvore encapsulada com contagem de acessos ao disco e comparações
 *
 * @param Ch Chave do Registro a ser removido
 *
 * @param Ap Arvore em que se esta removendo
 *
 * @param Diminuiu flag para alertar redução na altura da arvore
 *
 * @param dbg Debugger que armazenará contadores a serem incrementado
 *
 * Essa função irá:
 *
 * 1.Encontrar o registro a ser removido, contando o numero de acessos de leitura
 * 2.Remove-o, chamando as devidas funções auxiliares para reestruturar a arvore atendendo as regras da Arvore B, contando o numero de acessos de escrita
 */
void RetComContagem(TipoChave Ch, TipoApontador *Ap, short *Diminuiu,Debugger *dbg);
/**
 * @brief Função responsável por retirar registro da arvore com contagem de acessos ao disco e comparações
 *
 * @param Ch Chave do Registro a ser removido
 *
 * @param Ap Arvore em que se esta removendo
 *
 * @param dbg Debugger que armazenará contadores a serem incrementados
 *
 * Essa função encapsula a função RetComContagem reduzindo os numeros de parametros passados.
 */
void RetiraComContagem(TipoChave Ch, TipoApontador *Ap,Debugger *dbg);
/**
 * @brief Função responsável por Imprimir conteudo da Arvore B
 *
 * @param p Arvore a ser imprimida
 *
 * @param nivel variavel auxiliar para calcular nivel de altura acessado
 *
 * @param dbg Debugger que armazenará contadores a serem incrementados
 *
 * Essa função irá passar por todas as paginas imprimindo seus conteudos
 */
void ImprimeIComContagem(TipoApontador p, int nivel, Debugger *dbg);
/**
 * @brief Função responsável por encapsular a função ImprimeIComContagem
 *
 * @param p Arvore a ser imprimida
 *
 * @param dbg Debugger que armazenará contadores a serem incrementados
 *
 * Essa função encapsula a função ImprimeIComContagem reduzindo os numeros de parametros passados.
 */
void ImprimeComContagem(TipoApontador p,Debugger *dbg);
/**
 * @brief Função responsável por corrigir quebra das regras da Arvore B com contagem de acessos ao disco e comparações
 *
 * @param ApPag Pagina a ser tratada
 *
 * @param ApPai Pagina pai da pagina a ser tratada
 *
 * @param PosPai Indice da pagina a ser tratada no vetor de filhos da pagina pai
 *
 * @param Diminuiu flag ativada quando há uma diminuição na altura da arvore
 *
 * @param dbg Debugger que armazenará contadores a serem incrementados
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
void ReconstituiComContagem(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu, Debugger *dbg);
/**
 * @brief Função responsável por encontrar registro antecessor ao Ap com contagem de acessos ao disco e comparações
 *
 * @param Ap pagina onde sera inserido o antecessor
 *
 * @param Ind indice da pagina Ap no vetor de filhos de ApPai
 *
 * @param ApPai Pagina origem do antecessor
 *
 * @param Diminuiu flag ativada quando há uma diminuição na altura da arvore
 *
 * @param dbg Debugger que armazenará contadores a serem incrementados
 *
 * Essa função irá:
 *
 * 1. Percorrer a arvore pelas paginas à esquerda até encontrar o nó folha
 * 2. Capturar o maior registro do nó folha como sendo o antecessor
 */
void AntecessorComContagem(TipoApontador Ap, int Ind,TipoApontador ApPai, short *Diminuiu, Debugger *dbg);


#endif
