#ifndef ARVOREBARQUIVO_H_INCLUDED
#define ARVOREBARQUIVO_H_INCLUDED
#define MM 80
#include <stdio.h>
#include <string.h>
typedef struct {
	int ID;
	char *nome;
} Registro;
typedef struct _btree{
	struct _btree* Filhas[MM+1];
	Registro regs[MM];
} BTree;
void loadBTree(BTree *t);


#endif
