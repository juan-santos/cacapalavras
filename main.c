#include "ProcuraMatriz.h"
#include <pthread.h>
#include <time.h>

clock_t processoContinuo(int nroLinhas, int nroColunas, char ***palavrasProcuradas, TLetra ***texto);
clock_t pesquisaThreads(int nroLinhas, int nroColunas, char ***palavrasProcuradas, TLetra ***texto);
void procuraPalavra(int nroLinhas, int nroColunas, char **palavrasProcuradas, TLetra ***texto);

int main(){
    int nroLinhas = 0, nroColunas = 0;
    clock_t tempo = 0;

    //declaro as strings
    TLetra **texto = NULL;
    char **palavrasProcuradas = NULL;

    printf(" #### Threads - Caca-palavras ####");
    if(lerArquivo(&nroLinhas, &nroColunas, &palavrasProcuradas, &texto) == FALSE) {
        //se o arquivo não foi encontrado
        printf(" Problemas ao ler do arquivo\n");
        exit(-1);
    }

    tempo = processoContinuo(nroLinhas, nroColunas, &palavrasProcuradas, &texto);
    printf("\n\n ##Tempo continuo: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));

    printf("############################################################################\n");

    tempo = pesquisaThreads(nroLinhas, nroColunas, &palavrasProcuradas, &texto);
    printf("\n\n ##Tempo thread: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));

    if(escreverArquivoSaida(nroLinhas, nroColunas, &texto) == FALSE){
        printf(" Erro, nao foi possivel criar o arquivo\n");
        exit(-1);
    }

    free(texto);
    free(palavrasProcuradas);

    return 1;
}


clock_t processoContinuo(int nroLinhas, int nroColunas, char ***palavrasProcuradas, TLetra ***texto){
    int i;
    clock_t tInicio, tFim;

    tInicio = clock();
    for(i = 0; i < NUMERO_PALAVRAS; i++){
        procuraPalavra(nroLinhas, nroColunas, &(*palavrasProcuradas)[i],&(*texto));
    }

    tFim = clock();
    return (tFim - tInicio);
}


clock_t pesquisaThreads(int nroLinhas, int nroColunas, char ***palavrasProcuradas, TLetra ***texto){

    clock_t tInicio, tFim;
    int i = 0;

    tInicio = clock();
    for(i = 0; i < NUMERO_PALAVRAS; i++){
        procuraPalavra(nroLinhas, nroColunas, &(*palavrasProcuradas)[i],&(*texto));
    }

    tFim = clock();
    return (tFim - tInicio);
}


void procuraPalavra(int nroLinhas, int nroColunas, char **palavrasProcuradas, TLetra ***texto){
    printf("\n\n Procurando por: %s\n", (*palavrasProcuradas));

    if(procurarHorizontal(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarHorizontalInvertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarVertical(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarVerticalInvertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarDiagonal1(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarDiagonal1Invertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarDiagonal2(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }

    if(procurarDiagonal2Invertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &(*texto)) == ACHOU){
        return;
    }
}
