#include "ProcuraMatriz.h"

void inverter(char **palavraProcurada, char **palavraInvertida){
    int tamanhoPalavra = strlen(*palavraProcurada);
    int i = 0;

    //obtenho a palavra invertida
    while(tamanhoPalavra > 0){
        (*palavraInvertida)[i] = (*palavraProcurada)[tamanhoPalavra - 1];
        i++;
        tamanhoPalavra--;
    }
    (*palavraInvertida)[i] = '\0';
}


int horizontal(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    int tamanhoPalavra = strlen(*palavraProcurada);
    int i = 0, j = 0, substring = 0;

    tamanhoPalavra = strlen(*palavraProcurada);

    for(i = 0; i < *nroLinhas; i++){
        for(j = 0; j <= (*nroColunas - tamanhoPalavra); j++){
            char aux[NUMERO_LETRAS+1] = "";

            substring = 0;
            while(substring < tamanhoPalavra){
                aux[substring] = (*texto)[i][substring+j].letra;
                substring++;
            }
            aux[substring] = '\0';

            if(strcmp(aux, (*palavraProcurada)) == 0){
                //achou
                substring = 0;
                while(substring < tamanhoPalavra){
                    (*texto)[i][substring+j].achou = TRUE;
                    substring++;
                }
                textcolor(GREEN);
                printf("'%s' inicio:(%i,%i), fim: (%i,%i) \n", *palavraProcurada, i, j, i, substring+j);
                textcolor(WHITE);
                return ACHOU;
            }
        }
    }

    return NAO_ACHOU;
}
int procurarHorizontal(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    printf("Horizontal: ");
    return horizontal(&(*nroLinhas), &(*nroColunas), &(*palavraProcurada), &(*texto));
}
int procurarHorizontalInvertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));

    printf("Horizontal invertida: ");
    return horizontal(&(*nroLinhas), &(*nroColunas), &palavraInvertida, &(*texto));

}


int vertical(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    int tamanhoPalavra = strlen(*palavraProcurada);
    int i = 0, j = 0, substring = 0;

    tamanhoPalavra = strlen(*palavraProcurada);

    for(j = 0; j < *nroColunas; j++){
        for(i = 0; i <= (*nroLinhas - tamanhoPalavra); i++){
            char aux[NUMERO_LETRAS+1] = "";

            substring = 0;
            while(substring < tamanhoPalavra){
                aux[substring] = (*texto)[i+substring][j].letra;
                substring++;
            }
            aux[substring] = '\0';

            if(strcmp(aux, (*palavraProcurada)) == 0){
                //achou
                substring = 0;
                while(substring < tamanhoPalavra){
                    (*texto)[substring+i][j].achou = TRUE;
                    substring++;
                }
                textcolor(GREEN);
                printf("'%s' inicio: (%i,%i), fim: (%i,%i) \n", *palavraProcurada, i, j, i, substring+j);
                textcolor(WHITE);
                return ACHOU;
            }
        }
    }

    return NAO_ACHOU;
}
int procurarVertical(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    printf("Vertical: ");
    return vertical(&(*nroLinhas), &(*nroColunas), &(*palavraProcurada), &(*texto));
}
int procurarVerticalInvertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));

    printf("Vertical invertida: ");
    return vertical(&(*nroLinhas), &(*nroColunas), &palavraInvertida, &(*texto));
}


int diagonal1(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    return NAO_ACHOU;
}
int procurarDiagonal1(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    printf("Diagonal 1: ");
    return diagonal1(&(*nroLinhas), &(*nroColunas), &(*palavraProcurada), &(*texto));
}
int procurarDiagonal1Invertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));

    printf("Diagonal 1 invertida: ");
    return diagonal1(&(*nroLinhas), &(*nroColunas), &palavraInvertida, &(*texto));
}


int diagonal2(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    return NAO_ACHOU;
}
int procurarDiagonal2(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    printf("Diagonal 2: ");
    return diagonal2(&(*nroLinhas), &(*nroColunas), &(*palavraProcurada), &(*texto));
}
int procurarDiagonal2Invertido(int *nroLinhas, int *nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));

    printf("Diagonal 2 invertida: ");
    return diagonal2(&(*nroLinhas), &(*nroColunas), &palavraInvertida, &(*texto));
}

