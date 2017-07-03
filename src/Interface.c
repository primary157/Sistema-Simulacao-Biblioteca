#include "Interface.h"
void run_ui(TipoPaginaDebugger *Ap){
    Debugger dbg;
    short Parar = 0;
    State state = DEFAULT;
    int answer;
    resetDebugger(&dbg);
    while(!Parar){
        switch(state){
            case DEFAULT:
                printf("Menu Principal do Sistema Bibliotecário\n\n");
                printf("Escolha uma opção para prosseguirmos:\n1-Inserção\t2-Remoção\t3-Busca\t\t0-Fechar\n");
                scanf("%d",&answer);
                break;
            case INSERTION:
                printf("INSERINDO\n");
                state = ANALYSIS;
                break;
            case DELETION:
                
                printf("REMOVENDO\n");
                state = ANALYSIS;
                break;
            case SEARCH:
                
                printf("BUSCANDO\n");
                state = ANALYSIS;
                break;
            case ANALYSIS:
                
                printf("ANALISANDO\n");
                state = DEFAULT;
                break;
            
        }
        if (answer) state = (State)answer;
        else Parar = 1;
    }
    
}
