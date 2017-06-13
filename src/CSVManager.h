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
 * @brief Função responsável por 
 *
 * @param 
 *
 * Essa função irá:
 *
 * 1. 
 * 2. 
 */
int openFile(FILE **fptr, string fname);
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
FILE* findPosAndStoreNextText(FILE *fptr,int line, string *remainingText);
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
void addMatchToLine(FILE *fptr,string match, int line);
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
void changeLineMatches(FILE *fptr,stringArray matches, int line);
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
int getNextMatch(FILE *fptr,string *match);
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
void getNextLine(FILE *fptr, stringArray *matches);
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
void getRemainingMatches(FILE *fptr, linesOfStringArrays *matches);
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
void getAllMatches(FILE *fptr, stringArray **matches);

#endif
