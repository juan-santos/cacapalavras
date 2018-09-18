#ifndef PROCURAMATRIZ_H_INCLUDED
#define PROCURAMATRIZ_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "conio2.h"

#define TRUE 1
#define FALSE 0

#define NUMERO_PALAVRAS 6
#define NUMERO_LETRAS 10

#define ACHOU 1
#define NAO_ACHOU 0

#define SENTIDO_NORMAL 1
#define SENTIDO_INVERSO 0

typedef struct{
  char letra;
  int achou;
  //int cor;
  int linha;
  int coluna;
} TLetra;

int escreverArquivoSaida(int nroLinhas, int nroColunas, TLetra ***texto);
int lerArquivo(int *nroLinhas, int *nroColunas, char ***palavasProcuradas, TLetra ***texto);

int vertical(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao);
int horizontal(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao);
int diagonal1(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao);
int diagonal2(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao);

int procurarHorizontal(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarHorizontalInvertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarVertical(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarVerticalInvertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarDiagonal1(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarDiagonal1Invertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);

int procurarDiagonal2(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);
int procurarDiagonal2Invertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto);

void inverter(char **palavraProcurada, char **palavraInvertida);

#endif // PROCURAMATRIZ_H_INCLUDED
