#include "ArvoreDebugger.h"
void imprimeDebugger(Debugger *dbg){
	printf("comparacoes %u e acessos: %u, sendo %u de escrita e %u de leitura\n",
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
int altura(TipoApontador *Ap){
	if ((*Ap)->filhos[0] != NULL) return altura(&(*Ap)->filhos[0])+1;
	return 1;
}
void PesquisaComContagem(TipoRegistro *x, TipoApontador Ap,Debugger *dbg){
    long i = 1;
    if (Ap == NULL) {
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->tamanho_atual && x->Chave > Ap->registros[i-1].Chave) i++;
    if (x->Chave == Ap->registros[i-1].Chave) {
        *x = Ap->registros[i-1];
        return;
    }
    if (x->Chave < Ap->registros[i-1].Chave)
        PesquisaComContagem(x, Ap->filhos[i-1],dbg);
    else PesquisaComContagem(x, Ap->filhos[i],dbg);
}
void InsComContagem(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno,Debugger *dbg){
    long i = 1;
    long j;
    TipoApontador ApTemp;
    if (Ap == NULL) 
    {
        *Cresceu = TRUE;
        (*RegRetorno) = Reg;
        (*ApRetorno) = NULL;
        return;
    }
    while (i < Ap->tamanho_atual && Reg.Chave > Ap->registros[i-1].Chave)  i++;

    if (Reg.Chave == Ap->registros[i-1].Chave) {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }
    if (Reg.Chave < Ap->registros[i-1].Chave) i--;

    InsComContagem(Reg, Ap->filhos[i], Cresceu, RegRetorno, ApRetorno,dbg);
    if (!*Cresceu) return;
    if (Ap->tamanho_atual < MM) { /* Pagina tem espaco */
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = FALSE;
        return;
    }
    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->tamanho_atual = 0;
    ApTemp->filhos[0] = NULL;

    if (i < M + 1) {
        InsereNaPagina(ApTemp, Ap->registros[MM-1], Ap->filhos[MM]);
        Ap->tamanho_atual--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else {
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    }

    for (j = M + 2; j <= MM; j++){
        InsereNaPagina(ApTemp, Ap->registros[j-1], Ap->filhos[j]);
    }
    
    Ap->tamanho_atual = M;
    ApTemp->filhos[0] = Ap->filhos[M+1];
    *RegRetorno = Ap->registros[M];
    *ApRetorno = ApTemp;
	
}
void InsereComContagem(TipoRegistro Reg, TipoApontador *Ap,Debugger *dbg){
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    InsComContagem(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno,dbg);
    if (Cresceu) /* Arvore cresce na altura pela raiz */
    {
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));
        ApTemp->tamanho_atual = 1;
        ApTemp->registros[0] = RegRetorno;
        ApTemp->filhos[1] = ApRetorno;
        ApTemp->filhos[0] = *Ap;
        *Ap = ApTemp;
    }
}
void RetComContagem(TipoChave Ch, TipoApontador *Ap, short *Diminuiu,Debugger *dbg){
    long j, Ind = 1;
    TipoApontador Pag;
    if (*Ap == NULL) {
        printf("Erro: registro nao esta na arvore\n");
        *Diminuiu = FALSE;
        return;
    }
    Pag = *Ap;
    while (Ind < Pag->tamanho_atual && Ch > Pag->registros[Ind-1].Chave) Ind++;
    if (Ch == Pag->registros[Ind-1].Chave) {
        if (Pag->filhos[Ind-1] == NULL) { /* TipoPagina folha */
								//ISSO CONTA COMO ACESSO A DISCO?
            Pag->tamanho_atual--;
            *Diminuiu = (Pag->tamanho_atual < M);
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
    if (Ch > Pag->registros[Ind-1].Chave) Ind++;
    RetComContagem(Ch, &Pag->filhos[Ind-1], Diminuiu,dbg);
    if (*Diminuiu) Reconstitui(Pag->filhos[Ind-1], *Ap, Ind - 1, Diminuiu);
}
void RetiraComContagem(TipoChave Ch, TipoApontador *Ap,Debugger *dbg){
    short Diminuiu;
    TipoApontador Aux;
    RetComContagem(Ch, Ap, &Diminuiu,dbg);
    if (Diminuiu && (*Ap)->tamanho_atual == 0) { /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->filhos[0];
        free(Aux);
    }
	
}
void ImprimeIComContagem(TipoApontador p, int nivel, Debugger *dbg){
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
void ImprimeComContagem(TipoApontador p,Debugger *dbg){
    ImprimeIComContagem(p, 0,dbg);
}
void ReconstituiComContagem(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu, Debugger *dbg){
    TipoPagina *Aux;
    long DispAux, j;
    if (PosPai < ApPai->tamanho_atual) { /* Aux = TipoPagina a direita de ApPag */
        Aux = ApPai->filhos[PosPai+1];
        DispAux = (Aux->tamanho_atual - M + 1) / 2;
        ApPag->registros[ApPag->tamanho_atual] = ApPai->registros[PosPai];
        ApPag->filhos[ApPag->tamanho_atual + 1] = Aux->filhos[0];
        ApPag->tamanho_atual++;
        if (DispAux > 0) { /* Existe folga: transfere de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->registros[j-1], Aux->filhos[j]);
            ApPai->registros[PosPai] = Aux->registros[DispAux-1];
            Aux->tamanho_atual -= DispAux;
            for (j = 0; j < Aux->tamanho_atual; j++) Aux->registros[j] = Aux->registros[j + DispAux];
            for (j = 0; j <= Aux->tamanho_atual; j++) Aux->filhos[j] = Aux->filhos[j + DispAux];
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala Aux em ApPag e libera Aux */
            for (j = 1; j <= M; j++)
                InsereNaPagina(ApPag, Aux->registros[j-1], Aux->filhos[j]);
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
                InsereNaPagina(ApPag, Aux->registros[Aux->tamanho_atual - j],
                               Aux->filhos[Aux->tamanho_atual - j + 1]);
            ApPag->filhos[0] = Aux->filhos[Aux->tamanho_atual - DispAux + 1];
            ApPai->registros[PosPai-1] = Aux->registros[Aux->tamanho_atual - DispAux];
            Aux->tamanho_atual -= DispAux;
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala ApPag em Aux e libera ApPag */
            for (j = 1; j <= M; j++)
                InsereNaPagina(Aux, ApPag->registros[j-1], ApPag->filhos[j]);
            free(ApPag);
            ApPai->tamanho_atual--;
            if (ApPai->tamanho_atual >= M)  *Diminuiu = FALSE;
        }
    }
}

void AntecessorComContagem(TipoApontador Ap, int Ind,TipoApontador ApPai, short *Diminuiu, Debugger *dbg){
    if (ApPai->filhos[ApPai->tamanho_atual] != NULL) {
        AntecessorComContagem(Ap, Ind, ApPai->filhos[ApPai->tamanho_atual], Diminuiu,dbg);
        if (*Diminuiu)
            ReconstituiComContagem(ApPai->filhos[ApPai->tamanho_atual], ApPai, (long)ApPai->tamanho_atual, Diminuiu,dbg);
        return;
    }
    Ap->registros[Ind-1] = ApPai->registros[ApPai->tamanho_atual - 1];
    ApPai->tamanho_atual--;
    *Diminuiu = (ApPai->tamanho_atual < M);
}
