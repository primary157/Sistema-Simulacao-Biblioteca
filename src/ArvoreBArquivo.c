#include "ArvoreBArquivo.h"

void LerArquivo(TipoApontador *D){
    TipoRegistro x;
    FILE *arq;
    InicializaRegistro(&x);
    InicializaArvore(D);
    
    if((arq  = fopen(NOME_ARQUIVO, "r")) == NULL)
        printf("Erro na leitura do arquivo\n");

    while(!feof(arq))
    {
        fscanf(arq, "%lld %[A-Z a-z –()-C<>^;.=-_+}{}^` #$& , ' e- |*@!?!'':,.[]]", &x.Chave, x.information.nome_do_livro);
        printf("%lld -> %s\n", x.Chave,x.information.nome_do_livro);
        Insere(x, D);
    }
}
