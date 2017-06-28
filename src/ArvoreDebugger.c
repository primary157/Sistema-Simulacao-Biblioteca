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
	if ((*Ap)->p[0] != NULL) return altura(&(*Ap)->p[0])+1;
	return 1;
}
void PesquisaComContagem(TipoRegistro *x, TipoApontador Ap,Debugger *dbg){
    long i = 1;
    if (Ap == NULL) {
        printf("TipoRegistro nao esta presente na arvore\n");
        return;
    }
    while (i < Ap->n && x->Chave > Ap->r[i-1].Chave) i++;
    if (x->Chave == Ap->r[i-1].Chave) {
        *x = Ap->r[i-1];
        return;
    }
    if (x->Chave < Ap->r[i-1].Chave)
        PesquisaComContagem(x, Ap->p[i-1],dbg);
    else PesquisaComContagem(x, Ap->p[i],dbg);
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
    while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  i++;

    if (Reg.Chave == Ap->r[i-1].Chave) {
        printf(" Erro: Registro ja esta presente\n");
        *Cresceu = FALSE;
        return;
    }
    if (Reg.Chave < Ap->r[i-1].Chave) i--;

    InsComContagem(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno,dbg);
    if (!*Cresceu) return;
    if (Ap->n < MM) { /* Pagina tem espaco */
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = FALSE;
        return;
    }
    /* Overflow: Pagina tem que ser dividida */
    ApTemp = (TipoApontador)malloc(sizeof(TipoPagina));
    ApTemp->n = 0;
    ApTemp->p[0] = NULL;

    if (i < M + 1) {
        InsereNaPagina(ApTemp, Ap->r[MM-1], Ap->p[MM]);
        Ap->n--;
        InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else {
        InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
    }

    for (j = M + 2; j <= MM; j++){
        InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
    }
    
    Ap->n = M;
    ApTemp->p[0] = Ap->p[M+1];
    *RegRetorno = Ap->r[M];
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
        ApTemp->n = 1;
        ApTemp->r[0] = RegRetorno;
        ApTemp->p[1] = ApRetorno;
        ApTemp->p[0] = *Ap;
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
    while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++;
    if (Ch == Pag->r[Ind-1].Chave) {
        if (Pag->p[Ind-1] == NULL) { /* TipoPagina folha */
								//ISSO CONTA COMO ACESSO A DISCO?
            Pag->n--;
            *Diminuiu = (Pag->n < M);
            for (j = Ind; j <= Pag->n; j++){
                Pag->r[j-1] = Pag->r[j];			//SOBRESCREVE O REGISTRO
                Pag->p[j] = Pag->p[j+1];
            }
            return;
        }
        /* TipoPagina nao folha: trocar com antecessor */
        AntecessorComContagem(*Ap, Ind, Pag->p[Ind-1], Diminuiu,dbg);
        if (*Diminuiu)
            ReconstituiComContagem(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu,dbg);
        return;
    }
    if (Ch > Pag->r[Ind-1].Chave) Ind++;
    RetComContagem(Ch, &Pag->p[Ind-1], Diminuiu,dbg);
    if (*Diminuiu) Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
}
void RetiraComContagem(TipoChave Ch, TipoApontador *Ap,Debugger *dbg){
    short Diminuiu;
    TipoApontador Aux;
    RetComContagem(Ch, Ap, &Diminuiu,dbg);
    if (Diminuiu && (*Ap)->n == 0) { /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->p[0];
        free(Aux);
    }
	
}
void ImprimeIComContagem(TipoApontador p, int nivel, Debugger *dbg){
	long i;
	if (p == NULL) return;
	printf("Nivel %d : ", nivel);
	if(nivel) incAcessos_a_disco(ACESSO_DE_LEITURA,dbg);
	for (i = 0; i < p->n; i++)
		printf("%ld ",(long)p->r[i].Chave);
	putchar('\n');
	nivel++;
	for (i = 0; i <= p->n; i++){
		ImprimeIComContagem(p->p[i], nivel,dbg);
	}
}
void ImprimeComContagem(TipoApontador p,Debugger *dbg){
    ImprimeIComContagem(p, 0,dbg);
}
void ReconstituiComContagem(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu, Debugger *dbg){
    TipoPagina *Aux;
    long DispAux, j;
    if (PosPai < ApPai->n) { /* Aux = TipoPagina a direita de ApPag */
        Aux = ApPai->p[PosPai+1];
        DispAux = (Aux->n - M + 1) / 2;
        ApPag->r[ApPag->n] = ApPai->r[PosPai];
        ApPag->p[ApPag->n + 1] = Aux->p[0];
        ApPag->n++;
        if (DispAux > 0) { /* Existe folga: transfere de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            ApPai->r[PosPai] = Aux->r[DispAux-1];
            Aux->n -= DispAux;
            for (j = 0; j < Aux->n; j++) Aux->r[j] = Aux->r[j + DispAux];
            for (j = 0; j <= Aux->n; j++) Aux->p[j] = Aux->p[j + DispAux];
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala Aux em ApPag e libera Aux */
            for (j = 1; j <= M; j++)
                InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
            free(Aux);
            for (j = PosPai + 1; j < ApPai->n; j++) {
                ApPai->r[j-1] = ApPai->r[j];
                ApPai->p[j] = ApPai->p[j+1];
            }
            ApPai->n--;
            if (ApPai->n >= M) *Diminuiu = FALSE;
        }
    } else { /* Aux = TipoPagina a esquerda de ApPag */
        Aux = ApPai->p[PosPai-1];
        DispAux = (Aux->n - M + 1) / 2;
        for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag->r[j-1];
        ApPag->r[0] = ApPai->r[PosPai-1];
        for (j = ApPag->n; j >= 0; j--) ApPag->p[j+1] = ApPag->p[j];
        ApPag->n++;
        if (DispAux > 0) { /* Existe folga: transf. de Aux para ApPag */
            for (j = 1; j < DispAux; j++)
                InsereNaPagina(ApPag, Aux->r[Aux->n - j],
                               Aux->p[Aux->n - j + 1]);
            ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
            ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
            Aux->n -= DispAux;
            *Diminuiu = FALSE;
        } else { /* Fusao: intercala ApPag em Aux e libera ApPag */
            for (j = 1; j <= M; j++)
                InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
            free(ApPag);
            ApPai->n--;
            if (ApPai->n >= M)  *Diminuiu = FALSE;
        }
    }
}

void AntecessorComContagem(TipoApontador Ap, int Ind,TipoApontador ApPai, short *Diminuiu, Debugger *dbg){
    if (ApPai->p[ApPai->n] != NULL) {
        AntecessorComContagem(Ap, Ind, ApPai->p[ApPai->n], Diminuiu,dbg);
        if (*Diminuiu)
            ReconstituiComContagem(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu,dbg);
        return;
    }
    Ap->r[Ind-1] = ApPai->r[ApPai->n - 1];
    ApPai->n--;
    *Diminuiu = (ApPai->n < M);
}
