#ifndef CSVMANAGER_H_INCLUDED
#define CSVMANAGER_H_INCLUDED
#define CURRENT_LINE 0
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef char * string;
typedef string * stringArray;
typedef stringArray * linesOfStringArrays; 
int openFile(FILE **fptr, string fname);
FILE* findPosAndStoreNextText(FILE *fptr,int line, string *remainingText);
void addMatchToLine(FILE *fptr,string match, int line);
void changeLineMatches(FILE *fptr,stringArray matches, int line);
int getNextMatch(FILE *fptr,string *match);
void getNextLine(FILE *fptr, stringArray *matches);
void getRemainingMatches(FILE *fptr, linesOfStringArrays *matches);
void getAllMatches(FILE *fptr, stringArray **matches);

#endif
