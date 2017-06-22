/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao das funções do TAD modificado de Arvore B que faz uso de indexação 
 * por arquivos para leitura e escrita
 *
 * @details Nesse arquivo sobrescrevemos algumas funções básicas da implementação de Árvore B do Nivio Ziviani, 
 * dando a essa estrutura de dados a capacidade de gerenciar seus dados em arquivos de texto estruturados
 *
 * @copyright [GNU Public License 3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)
 */
#ifndef CSVMANAGER_H_INCLUDED
#define CSVMANAGER_H_INCLUDED
#define CURRENT_LINE 0
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef char * string;
typedef string * stringArray;
typedef stringArray * linesOfStringArrays; 
/**
 * @brief Função responsável por Abrir arquivo CSV
 *
 * @param fptr Ponteiro para arquivo a ser aberto
 * @param fname nome do arquivo a ser aberto
 *
 * Essa função irá:
 *
 * 1. Abrir arquivo de nome fname atribuindo-o a fptr;
 * 2. Retorna 1 caso tenha sucesso e Retorna 0 caso tenha falhado.
 * 
 * @return 1 para sucesso na leitura/0 para falha na leitura
 */
int openFile(FILE **fptr, string fname);
/**
 * @brief Função responsável por capturar texto contido no próximo item de mesma linha
 *
 * @param fptr Ponteiro para arquivo sendo lido
 * @param match Texto a ser populado pelo conteudo do item lido
 *
 * Essa função irá:
 *
 * 1. avançar ponteiro FILE para próximo item
 * 2. ler próximo e retorna 1 se não for fim da linha
 * 3. não lê nada e retorna 0 se for fim da linha (assim ao termino da execução o ponteiro FILE estará apontando para a próxima linha)
 * 
 * @return 1 se o item foi lido com sucesso/0 se não havia item na linha a ser lido(avança para a proxima linha);
 */
int getNextMatch(FILE *fptr,string *match);
/**
 * @brief Função responsável por capturar texto de todos itens contido na linha
 *
 * @param fptr Ponteiro para arquivo sendo lido
 * @param matches Array de Textos a ser populado pelo conteudo dos itens lido
 *
 * Essa função irá:
 *
 * 1. Chamar a função getNextMatch repetidas vezes esperando pelo retorno 0
 * 
 */
void getNextLine(FILE *fptr, stringArray *matches);
/**
 * @brief Função responsável por capturar texto de todos itens contido em todas as linhas subsequentes
 *
 * @param fptr Ponteiro para arquivo sendo lido
 * @param matches Array de Arrays de Textos a ser populado pelo conteudo das linhas lida
 *
 * Essa função irá:
 *
 * 1. Chamar a função getNextLine repetidas vezes esperando EOF.
 */
void getRemainingMatches(FILE *fptr, linesOfStringArrays *matches);
/**
 * @brief Função responsável por capturar texto de todos itens contido em todas as linhas do texto
 *
 * @param fptr Ponteiro para arquivo sendo lido
 * @param matches Array de Arrays de Textos a ser populado pelo conteudo das linhas lida
 *
 * Essa função irá:
 *
 * 1. Retornar o ponteiro FILE para o inicio do arquivo;
 * 2. Chamar a função getRemainingMatches.
 */
void getAllMatches(FILE *fptr, stringArray **matches);
/**
 * @brief Função responsável por encontrar posição da primeira recorrencia de um dado match
 *
 * @param fptr Ponteiro para o arquivo a ser examinado
 * @param match	string com o match a ser procurado
 *
 * Essa função irá:
 *
 * 1. Percorrer cada item comparando o primeiro caracter com o primeiro caracter de match
 * 2. Se encontrar algum match que bata o primeiro caracter ele ira comparar todo o texto do match
 * 3. Por fim será retornado a posição de inicio do match encontrado ou -1 caso nao seja encontrado
 */
long findMatch(FILE *fptr, string match);
#endif
