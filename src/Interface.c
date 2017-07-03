#include "Interface.h"
void run_ui(TipoPaginaDebugger *Ap){
    TipoRegistro temp_reg;
    TipoChave temp_chave;
    Debugger dbg;
    short Parar = 0;
    State state = START;
    int answer;
    resetDebugger(&dbg);
    resetContadorPaginaRaiz(Ap);
    while(!Parar){
        switch(state){
            case START:
                printf("Menu Principal do Sistema Bibliotecário\n\n");
                printf("Escolha uma opção para prosseguirmos:\n1-Inserção\t2-Remoção\t3-Busca\t\t0-Fechar\n");
                scanf("%d",&answer);
                if(answer == 0) return;
                break;
            case INSERTION:
                printf("INSERINDO\n");
                printf("Digite o ISBN do livro a ser inserido(todos os 13 caracteres)\n");
                scanf("%lld",&temp_reg.Chave);
                printf("Digite o nome do livro a ser inserido(maximo de 200 caracteres)\n");
                scanf("%200s",temp_reg.information.nome_do_livro);
                InsereComContagem(temp_reg,&Ap,&dbg);
                answer = -1;
                state = ANALYSIS;
                break;
            case DELETION:
                printf("REMOVENDO\n");
                printf("Digite o ISBN do livro a ser removido(todos os 13 caracteres)\n");
                scanf("%lld",&temp_chave);
                RetiraComContagem(temp_chave,&Ap,&dbg);
                answer = -1;
                state = ANALYSIS;
                break;
            case SEARCH:
                printf("BUSCANDO\n");
                printf("Digite o ISBN do livro a ser buscado(todos os 13 caracteres)\n");
                scanf("%lld",&temp_reg.Chave);
                printf("Registro%s Encontrado!\n",PesquisaComContagem(&temp_reg,Ap,&dbg)?"":" não");
                answer = -1;
                state = ANALYSIS;
                break;
            case ANALYSIS:
                printf("ANALISANDO\n");
                imprimeDebugger(&dbg);
                resetDebugger(&dbg);
                resetContadorPaginaRaiz(Ap);
                answer = -1;
                state = START;
                break;
            default:
                printf("Valor inválido\n");
                answer = -1;
                state = START;
        }
        if(answer != -1) state = answer != 4 ? (State)answer : 5;
    }
    
}
