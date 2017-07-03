/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao da função de interpretação de arquivos para criação da Arvore B a partir de uma entrada de texto
 *
 * @details Nesse arquivo implementamos um algoritmo que liga a funcionalidade de inserção na Árvore B do Nivio Ziviani, 
 * com a biblioteca de leitura de arquivos CSV implementada pela dupla.
 */

#ifndef ARVOREBARQUIVO_H_INCLUDED
#define ARVOREBARQUIVO_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "arvB.h"

#define NOME_ARQUIVO "teste2.txt"

/**
 * @brief Função responsável por interpretar arquivo de entrada e executar a inicialização de suas paginas, chamando as funções necessárias para isso
 *
 * @param D Ponteiro para Pagina raiz da Árvore B a ser preenchida com dados do arquivo
 *
 * Essa função irá:
 *
 * 1. Abrir arquivo, atribuir valores as variaveis de um registro temporário
 * 2. Inserir registro à arvore
 * 3. Repetir os passos 1 e 2 até o fim do arquivo (EOF)
 */
void LerArquivo(TipoApontador *D);



#endif
