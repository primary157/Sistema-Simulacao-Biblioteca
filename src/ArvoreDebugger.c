#include "ArvoreDebugger.h"
void resetContadorPagina(TipoPaginaDebugger* Ap){
    int i;
    if(Ap == NULL) return;
    Ap->Modificada = 0;
    Ap->Na_Mem_Principal = 0;
    for (i = 0; i <= Ap->tamanho_atual; i++){
        resetContadorPagina(Ap->filhos[i]);
    }
}
void resetContadorPaginaRaiz(TipoPaginaDebugger* Ap){
    int i;
    Ap->Modificada = 0;
    Ap->Na_Mem_Principal = 1;
    if(Ap->filhos[Ap->tamanho_atual] != NULL){
        for (i = 0; i <= Ap->tamanho_atual; i++){
            resetContadorPagina(Ap->filhos[i]);
        }
    }
}
void imprimeDebugger(Debugger *dbg){
	printf("Foram feitas %u comparações e %u acessos, sendo %u de escrita e %u de leitura\n",
	dbg->comparacoes,
	dbg->num_acessos_a_disco.total,
	dbg->num_acessos_a_disco.escrita,
	dbg->num_acessos_a_disco.leitura);
	
}
void resetDebugger(Debugger *dbg){
	dbg->comparacoes = 0;
	dbg->num_acessos_a_disco.escrita = 0;
	dbg->num_acessos_a_disco.total = 0;
	dbg->num_acessos_a_disco.leitura = 0;
}
void incComparacoes(Debugger *dbg){
	dbg->comparacoes++;
}
void incAcessos_a_disco(TipoDeAcesso tipo_de_acesso,Debugger *dbg){
	dbg->num_acessos_a_disco.total++;
	if(tipo_de_acesso == ACESSO_DE_ESCRITA){
		dbg->num_acessos_a_disco.escrita++;
		return;
	}
	dbg->num_acessos_a_disco.leitura++;
}
int altura(TipoApontador Ap){
	if (Ap->filhos[0] != NULL) return altura(Ap->filhos[0])+1;
	return 1;
}
short PesquisaComContagem(TipoRegistro *x, TipoPaginaDebugger *Ap,Debugger *dbg){
    long i = 1, c_comp;
    if (Ap == NULL) {
        printf("TipoRegistro nao esta presente na arvore\n");
        return 0;
    }else if(!Ap->Na_Mem_Principal){ 
        incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);   //contando acessos a disco
        Ap->Na_Mem_Principal = 1;                    //setando flag de leitura
    }
    while (i < Ap->tamanho_atual && x->Chave > Ap->registros[i-1].Chave) i++;
    c_comp = i; //numero de comparacoes = numero de acertos da condição + 1 (valor inicial de i)
    while(c_comp--) incComparacoes(dbg);    //contando comparações do while
    
    
    incComparacoes(dbg);                    //contando comparações do prox if
    if (x->Chave == Ap->registros[i-1].Chave) { //Achou
        *x = Ap->registros[i-1];
        return 1;
    }
    incComparacoes(dbg);                    //contando comparações do prox if
    if (x->Chave < Ap->registros[i-1].Chave)
        return PesquisaComContagem(x, Ap->filhos[i-1],dbg);
    else return PesquisaComContagem(x, Ap->filhos[i],dbg);
}
void InsComContagem(TipoRegistro Reg, TipoPaginaDebugger *Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoPaginaDebugger **ApRetorno,Debugger *dbg){
    long i = 1, c_comp;
    long j;
    TipoPaginaDebugger *ApTemp;
    if (Ap == NULL){
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }else if(!Ap->Na_Mem_Principal){ 
        incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);   //contando acessos a disco
        Ap->Na_Mem_Principal = 1;                    //setando flag de leitura
    }
    while (i < Ap->tamanho_atual && Reg.Chave > Ap->registros[i-1].Chave)  i++;
    c_comp = i; //numero de comparacoes = numero de acertos da condição + 1 (valor inicial de i)
    while(c_comp--) incComparacoes(dbg);    //contando comparações do while
    
    incComparacoes(dbg);                    //contando comparações do prox if
    if (Reg.Chave == Ap->registros[i-1].Chave) {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }
    incComparacoes(dbg);                    //contando comparações do prox if
    if (Reg.Chave < Ap->registros[i-1].Chave) i--;

    InsComContagem(Reg, Ap->filhos[i], Cresceu, RegRetorno, ApRetorno,dbg);
    if (!*Cresceu) return;
    if (Ap->tamanho_atual < MM) { /* Pagina tem espaco */
        InsereNaPaginaComContagem(Ap, *RegRetorno, *ApRetorno,dbg);
        *Cresceu = FALSE;
        return;
    }
    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (TipoPaginaDebugger *)malloc(sizeof(TipoPaginaDebugger));
    ApTemp->tamanho_atual = 0;
    ApTemp->filhos[0] = NULL;
    ApTemp->Na_Mem_Principal = 1;   //Evitar contagem de acesso de leitura na página criada
    
    if (i < M + 1) { //Decidindo onde vai o registro inserido
        InsereNaPaginaComContagem(ApTemp, Ap->registros[MM-1], Ap->filhos[MM],dbg);
        Ap->tamanho_atual--;
        InsereNaPaginaComContagem(Ap, *RegRetorno, *ApRetorno,dbg);
    } else {
        InsereNaPaginaComContagem(ApTemp, *RegRetorno, *ApRetorno,dbg);
    }

    for (j = M + 2; j <= MM; j++){
        InsereNaPaginaComContagem(ApTemp, Ap->registros[j-1], Ap->filhos[j],dbg);
    }
    
    Ap->tamanho_atual = M;
    ApTemp->filhos[0] = Ap->filhos[M+1];
    *RegRetorno = Ap->registros[M];
    *ApRetorno = ApTemp;
	
}
void InsereComContagem(TipoRegistro Reg, TipoPaginaDebugger **Ap,Debugger *dbg){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPaginaDebugger *ApRetorno, *ApTemp;
    InsComContagem(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno,dbg); //RegRetorno é o registro que sobe e ApRetorno é o filho a direita
    if (Cresceu) /* Arvore cresce na altura pela raiz */
    {
        ApTemp = (TipoPaginaDebugger *)malloc(sizeof(TipoPaginaDebugger));
        ApTemp->tamanho_atual = 1;
        ApTemp->registros[0] = RegRetorno;
        ApTemp->filhos[1] = ApRetorno;
        ApTemp->filhos[0] = *Ap;
        *Ap = ApTemp;
    }
}
void RetComContagem(TipoChave Ch, TipoPaginaDebugger **Ap, short *Diminuiu,Debugger *dbg){
    long j, Ind = 1, c_comp;
    TipoPaginaDebugger *Pag;
    if (*Ap == NULL) {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }else if(!(*Ap)->Na_Mem_Principal){ 
        incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);   //contando acessos a disco
        (*Ap)->Na_Mem_Principal = 1;                    //setando flag de leitura
    }
    Pag = *Ap;
    while (Ind < Pag->tamanho_atual && Ch > Pag->registros[Ind-1].Chave) Ind++;
    c_comp = Ind; //numero de comparacoes = numero de acertos da condição + 1 (valor inicial de Ind)
    while(c_comp--) incComparacoes(dbg);    //contando comparações do while
    
    incComparacoes(dbg);                    //contando comparações do prox if
    if (Ch == Pag->registros[Ind-1].Chave) {
        if (Pag->filhos[Ind-1] == NULL) { /* TipoPagina folha */
								//ISSO CONTA COMO ACESSO A DISCO?
            Pag->tamanho_atual--;
            *Diminuiu = (Pag->tamanho_atual < M);//Quebrou a regra?
            if(!Pag->Modificada){
                Pag->Modificada = 1;
                incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
            }
            for (j = Ind; j <= Pag->tamanho_atual; j++){
                Pag->registros[j-1] = Pag->registros[j];			//SOBRESCREVE O REGISTRO
                Pag->filhos[j] = Pag->filhos[j+1];
            }
            return;
        }
        /* TipoPagina nao folha: trocar com antecessor */
        AntecessorComContagem(*Ap, Ind, Pag->filhos[Ind-1], Diminuiu,dbg);
        if (*Diminuiu)
            ReconstituiComContagem(Pag->filhos[Ind-1], *Ap, Ind - 1, Diminuiu,dbg);
        return;
    }
    incComparacoes(dbg);                    //contando comparações do prox if
    if (Ch > Pag->registros[Ind-1].Chave) Ind++;
    RetComContagem(Ch, &Pag->filhos[Ind-1], Diminuiu,dbg);
    if (*Diminuiu) ReconstituiComContagem(Pag->filhos[Ind-1], *Ap, Ind - 1, Diminuiu, dbg);
}
void RetiraComContagem(TipoChave Ch, TipoPaginaDebugger **Ap,Debugger *dbg){
    short Diminuiu;
    TipoPaginaDebugger *Aux;
    RetComContagem(Ch, Ap, &Diminuiu,dbg);
    if (Diminuiu && (*Ap)->tamanho_atual == 0) { /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->filhos[0];
        free(Aux);
    }	
}
void ImprimeIComContagem(TipoPaginaDebugger *p, int nivel, Debugger *dbg){
	long i;
	if (p == NULL) return;
	printf("Nivel %d : ", nivel);
	if(nivel) incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);
	for (i = 0; i < p->tamanho_atual; i++)
		printf("%ld ",(long)p->registros[i].Chave);
	putchar('\n');
	nivel++;
	for (i = 0; i <= p->tamanho_atual; i++){
		ImprimeIComContagem(p->filhos[i], nivel,dbg);
	}
}
void ImprimeComContagem(TipoPaginaDebugger *p,Debugger *dbg){
    ImprimeIComContagem(p, 0,dbg);
}
void ReconstituiComContagem(TipoPaginaDebugger *ApPag, TipoPaginaDebugger *ApPai,int PosPai, short *Diminuiu, Debugger *dbg){
    TipoPaginaDebugger *Aux;
    long DispAux, j, c_comp;
    /*if(!ApPag->Modificada){
        if(!ApPag->Na_Mem_Principal){
            ApPag->Na_Mem_Principal = 1;      //Seta flag de modificação
            incAcessos_a_disco(ACESSO_DE_LEITURA, dbg);
        }
        ApPag->Modificada = 1;
        incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
    }
    */
    if (PosPai < ApPai->tamanho_atual) { /* Aux = TipoPagina a direita de ApPag */
        Aux = ApPai->filhos[PosPai+1];
        DispAux = (Aux->tamanho_atual - M + 1) / 2;
        ApPag->registros[ApPag->tamanho_atual] = ApPai->registros[PosPai];
        ApPag->filhos[ApPag->tamanho_atual + 1] = Aux->filhos[0];
        ApPag->tamanho_atual++;
        if (DispAux > 0) { /* Existe folga: transfere de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPaginaComContagem(ApPag, Aux->registros[j-1], Aux->filhos[j], dbg);
            ApPai->registros[PosPai] = Aux->registros[DispAux-1];
            Aux->tamanho_atual -= DispAux;
            for (j = 0; j < Aux->tamanho_atual; j++) Aux->registros[j] = Aux->registros[j + DispAux];
            for (j = 0; j <= Aux->tamanho_atual; j++) Aux->filhos[j] = Aux->filhos[j + DispAux];
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala Aux em ApPag e libera Aux */
            for (j = 1; j <= M; j++)
                InsereNaPaginaComContagem(ApPag, Aux->registros[j-1], Aux->filhos[j], dbg);
            free(Aux);
            for (j = PosPai + 1; j < ApPai->tamanho_atual; j++) {
                ApPai->registros[j-1] = ApPai->registros[j];
                ApPai->filhos[j] = ApPai->filhos[j+1];
            }
            ApPai->tamanho_atual--;
            if (ApPai->tamanho_atual >= M) *Diminuiu = FALSE;
        }
    } else { /* Aux = TipoPagina a esquerda de ApPag */
        Aux = ApPai->filhos[PosPai-1];
        DispAux = (Aux->tamanho_atual - M + 1) / 2;
        for (j = ApPag->tamanho_atual; j >= 1; j--) ApPag->registros[j] = ApPag->registros[j-1];
        ApPag->registros[0] = ApPai->registros[PosPai-1];
        for (j = ApPag->tamanho_atual; j >= 0; j--) ApPag->filhos[j+1] = ApPag->filhos[j];
        ApPag->tamanho_atual++;
        if (DispAux > 0) { /* Existe folga: transf. de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPaginaComContagem(ApPag, Aux->registros[Aux->tamanho_atual - j],
                               Aux->filhos[Aux->tamanho_atual - j + 1], dbg);
            ApPag->filhos[0] = Aux->filhos[Aux->tamanho_atual - DispAux + 1];
            ApPai->registros[PosPai-1] = Aux->registros[Aux->tamanho_atual - DispAux];
            Aux->tamanho_atual -= DispAux;
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala ApPag em Aux e libera ApPag */
            for (j = 1; j <= M; j++)
                InsereNaPaginaComContagem(Aux, ApPag->registros[j-1], ApPag->filhos[j], dbg);
            free(ApPag);
            ApPai->tamanho_atual--;
            if (ApPai->tamanho_atual >= M)  *Diminuiu = FALSE;
        }
    }
    
    if(!ApPai->Modificada){         //PAGINA
        if(!ApPai->Na_Mem_Principal){
            ApPai->Na_Mem_Principal = 1;      //Seta flag de modificação
            incAcessos_a_disco(ACESSO_DE_LEITURA, dbg);
        }
        ApPai->Modificada = 1;
        incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
    }
    if(!ApPag->Modificada){         //PAGINA
        if(!ApPag->Na_Mem_Principal){
            ApPag->Na_Mem_Principal = 1;      //Seta flag de modificação
            incAcessos_a_disco(ACESSO_DE_LEITURA, dbg);
        }
        ApPag->Modificada = 1;
        incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
    }
    if(!Aux->Modificada){           //IRMA
        if(!Aux->Na_Mem_Principal){
            Aux->Na_Mem_Principal = 1;      //Seta flag de modificação
            incAcessos_a_disco(ACESSO_DE_LEITURA, dbg);
        }
        Aux->Modificada = 1;
        incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
    }
}
void AntecessorComContagem(TipoPaginaDebugger *Ap, int Ind,TipoPaginaDebugger *ApPai, short *Diminuiu, Debugger *dbg){
    if (ApPai->filhos[ApPai->tamanho_atual] != NULL) {
        if(!Ap->Na_Mem_Principal){ 
            incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);   //contando acessos a disco
            Ap->Na_Mem_Principal = 1;                    //setando flag de leitura
        }
        AntecessorComContagem(Ap, Ind, ApPai->filhos[ApPai->tamanho_atual], Diminuiu,dbg);
        if (*Diminuiu)
            ReconstituiComContagem(ApPai->filhos[ApPai->tamanho_atual], ApPai, (long)ApPai->tamanho_atual, Diminuiu,dbg);
        return;
    }
    Ap->registros[Ind-1] = ApPai->registros[ApPai->tamanho_atual - 1];
    ApPai->tamanho_atual--;
    *Diminuiu = (ApPai->tamanho_atual < M);
}
void InsereNaPaginaComContagem(TipoPaginaDebugger *Ap, TipoRegistro Reg, TipoPaginaDebugger *ApDir, Debugger *dbg){
    short NaoAchouPosicao;
    int k;
    if(!Ap->Modificada){
        if(!Ap->Na_Mem_Principal){
            Ap->Na_Mem_Principal = 1;      //Seta flag de modificação
            incAcessos_a_disco(ACESSO_DE_LEITURA, dbg);
        }
        Ap->Modificada = 1;
        incAcessos_a_disco(ACESSO_DE_ESCRITA, dbg);
    }
    
    k = Ap->tamanho_atual;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao) {
        incComparacoes(dbg);                    //contando comparações do prox if
        if (Reg.Chave >= Ap->registros[k-1].Chave) {
            NaoAchouPosicao = FALSE;
            break;
        }
        Ap->registros[k] = Ap->registros[k-1];
        Ap->filhos[k+1] = Ap->filhos[k];
        k--;
        if (k < 1) NaoAchouPosicao = FALSE;
    }
    Ap->registros[k] = Reg;
    Ap->filhos[k+1] = ApDir;
    Ap->tamanho_atual++;
}
TipoPaginaDebugger* PAGINADEBUGGER(TipoApontador Ap){
    TipoPaginaDebugger* novoAp = (TipoPaginaDebugger*)malloc(sizeof(TipoPaginaDebugger));
    int i;
    if(Ap == NULL) return NULL;
    for(i = 0; i < MM; i++){
        novoAp->filhos[i] = PAGINADEBUGGER(Ap->filhos[i]);
        novoAp->registros[i] = Ap->registros[i];
    }
    novoAp->filhos[i] = PAGINADEBUGGER(Ap->filhos[i]);
    novoAp->tamanho_atual = Ap->tamanho_atual;
    novoAp->Modificada = 0;
    novoAp->Na_Mem_Principal = 0;
    return novoAp;
}
TipoApontador PAGINA(TipoPaginaDebugger *Ap){
    TipoApontador novoAp = (TipoApontador)malloc(sizeof(TipoPagina));
    int i;
    if(Ap == NULL) return NULL;
    for(i = 0; i < MM; i++){
        novoAp->filhos[i] = PAGINA(Ap->filhos[i]);
        novoAp->registros[i] = Ap->registros[i];
    }
    novoAp->filhos[i] = PAGINA(Ap->filhos[i]);
    novoAp->tamanho_atual = Ap->tamanho_atual;
    return novoAp;
    
}
