/**
 * @file
 * @author "Victor Guerra Veloso e Luan Henrique Silva Alves"
 * @date "13/06/2017"
 * @brief Arquivo de Implementacao da interface de usuário
 *
 * @details Nesse arquivo criamos uma interface de usuário (UI) baseada em linha de comando (CLI) para o usuário interagir com nosso sistema bibliotecário
 */
#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "ArvoreDebugger.h"
typedef enum State{DEFAULT,INSERTION,DELETION,SEARCH,ANALYSIS} State;
/**
 * @brief Função responsável por iniciar execução da UI
 *
 * @param Ap Arvore Populada com a qual o usuário irá interagir
 *
 * Essa função encapsula os passos relacionadas a interface de usuário (UI)
 */
void run_ui(TipoPaginaDebugger *Ap);
#endif
