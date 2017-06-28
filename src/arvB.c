#include "arvB.h"

void InicializaArvore(TipoApontador *pagina){
	int i;
	(*pagina) = (TipoApontador)malloc(sizeof(TipoPagina));
	(*pagina)->tamanho_atual = 0;
	for (i = 0; i < MM; i++) {
		(*pagina)->filhos[i] = NULL;
		InicializaRegistro((*pagina)->registros + i);

	}
	(*pagina)->filhos[i] = NULL;
}
void InicializaRegistro(TipoRegistro *reg){
    reg->Chave = 0.0;
    strcpy(reg->information.nome_do_autor,"");
    strcpy(reg->information.nome_do_livro,"");
    reg->information.numero_de_exemplares = 0;
}
void Pesquisa(TipoRegistro *x, TipoApontador Ap){
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
        Pesquisa(x, Ap->filhos[i-1]);
    else Pesquisa(x, Ap->filhos[i]);
}

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir){
    short NaoAchouPosicao;
    int k;
    k = Ap->tamanho_atual;
    NaoAchouPosicao = (k > 0);
    while (NaoAchouPosicao) {
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

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno,  TipoApontador *ApRetorno){
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

    Ins(Reg, Ap->filhos[i], Cresceu, RegRetorno, ApRetorno);
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

void Insere(TipoRegistro Reg, TipoApontador *Ap){ /*encapsulamento da função Ins()*/
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
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

void Reconstitui(TipoApontador ApPag, TipoApontador ApPai,int PosPai, short *Diminuiu){
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
                InsereNaPagina(ApPag, Aux->registros[Aux->tamanho_atual - j],Aux->filhos[Aux->tamanho_atual - j + 1]);
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

void Antecessor(TipoApontador Ap, int Ind,TipoApontador ApPai, short *Diminuiu){
    if (ApPai->filhos[ApPai->tamanho_atual] != NULL) {
        Antecessor(Ap, Ind, ApPai->filhos[ApPai->tamanho_atual], Diminuiu);
        if (*Diminuiu)
            Reconstitui(ApPai->filhos[ApPai->tamanho_atual], ApPai, (long)ApPai->tamanho_atual, Diminuiu);
        return;
    }
    Ap->registros[Ind-1] = ApPai->registros[ApPai->tamanho_atual - 1];
    ApPai->tamanho_atual--;
    *Diminuiu = (ApPai->tamanho_atual < M);
}

void Ret(TipoChave Ch, TipoApontador *Ap, short *Diminuiu){
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
            Pag->tamanho_atual--;
            *Diminuiu = (Pag->tamanho_atual < M);
            for (j = Ind; j <= Pag->tamanho_atual; j++) {
                Pag->registros[j-1] = Pag->registros[j];
                Pag->filhos[j] = Pag->filhos[j+1];
            }
            return;
        }
        /* TipoPagina nao e folha: trocar com antecessor */
        Antecessor(*Ap, Ind, Pag->filhos[Ind-1], Diminuiu);
        if (*Diminuiu)
            Reconstitui(Pag->filhos[Ind-1], *Ap, Ind - 1, Diminuiu);
        return;
    }
    if (Ch > Pag->registros[Ind-1].Chave) Ind++;
    Ret(Ch, &Pag->filhos[Ind-1], Diminuiu);
    if (*Diminuiu) Reconstitui(Pag->filhos[Ind-1], *Ap, Ind - 1, Diminuiu);
}

void Retira(TipoChave Ch, TipoApontador *Ap){
    short Diminuiu;
    TipoApontador Aux;
    Ret(Ch, Ap, &Diminuiu);
    if (Diminuiu && (*Ap)->tamanho_atual == 0) { /* Arvore diminui na altura */
        Aux = *Ap;
        *Ap = Aux->filhos[0];
        free(Aux);
    }
}

void ImprimeI(TipoApontador p, int nivel){
    long i;
    if (p == NULL) return;
    printf("Nivel %d : ", nivel);
    for (i = 0; i < p->tamanho_atual; i++)
        printf("%ld ",(long)p->registros[i].Chave);
    putchar('\n');
    nivel++;
    for (i = 0; i <= p->tamanho_atual; i++)
        ImprimeI(p->filhos[i], nivel);
}

void Imprime(TipoApontador p){
    int  n = 0;
    ImprimeI(p, n);
}

void TestaI(TipoApontador p, int pai, short direita){
    int i;
    int antecessor = 0;
    if (p == NULL) return;
    if (p->registros[0].Chave > pai && direita == FALSE) {
        printf("Erro: filho %12ld maior que pai %d\n", p->registros[0].Chave, pai);
        return;
    }
    for (i = 0; i < p->tamanho_atual; i++) {
        if (p->registros[i].Chave <= antecessor) {
            printf("Erro: irmao %ld maior que irmao a esquerda %d\n",
                   (long)p->registros[i].Chave, antecessor);
            return;
        }
        antecessor = p->registros[i].Chave;
    }
    for (i = 0; i < p->tamanho_atual; i++)
        TestaI(p->filhos[i], p->registros[i].Chave, FALSE);
    TestaI(p->filhos[p->tamanho_atual], p->registros[i].Chave, TRUE);
}

void Testa(TipoApontador p){
    int i;
    if (p == NULL) return;
    for (i = 0; i < p->tamanho_atual; i++)
        TestaI(p->filhos[i], p->registros[i].Chave, FALSE);
    TestaI(p->filhos[p->tamanho_atual], p->registros[i].Chave, TRUE);
}
