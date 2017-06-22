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
 * @brief Função responsável por Inicializar página da Arvore B
 *
 * @param pagina Ponteiro para ponteiro de pagina que sera responsavel por amazenar pagina alocada
 * Essa função irá:
 *
 * 1. Alocar espaço para a pagina
 * 2. Inicializar os registros com um valor inicial padrão
 */
void ArvoreComArquivo_Inicializa(TipoPagina **pagina);

/**
 * @brief Função responsável por interpretar arquivo de entrada e executar a inicialização de suas paginas, chamando as funções necessárias para isso
 *
 * @param PaginaMae Ponteiro para Pagina com arquivo referente à Pagina Mae do No que sera aberto
 * @param fptr Ponteiro para arquivo que sera lido
 * @param i Indice do Registro da PaginaMae que tem como filho o parametro Pagina
 *
 * Essa função irá:
 *
 * 1. Abrir arquivo, atribuir valores as variaveis da pagina
 * 2. Fazer chamada recursiva para nó filho da esquerda
 * 3. Fazer chamada recursiva para nó filho da direita
 */
void LerArquivo(TipoPagina *PaginaMae, int i, FILE **fptr);



#endif
