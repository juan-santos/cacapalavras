#ifndef PROCURAMATRIZ_H_INCLUDED
#define PROCURAMATRIZ_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include"conio2.h"

#define TRUE 1
#define FALSE 0
#define NUMERO_PALAVRAS 6
#define NUMERO_LETRAS 10
#define ACHOU 1
#define NAO_ACHOU 0

#define PRETO 1

typedef struct{
  char letra;
  int achou;
  int cor;
} TLetra;

int vertical(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
int horizontal(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarHorizontal(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarHorizontalInvertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarVertical(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarVerticalInvertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarDiagonal1(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarDiagonal1Invertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarDiagonal2(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarDiagonal2Invertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

void inverter(char **palavraProcurada, char **palavraInvertida);

//int procurarDiagonal(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);
//int procurarDiagonalInvertida(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto);

#endif // PROCURAMATRIZ_H_INCLUDED
