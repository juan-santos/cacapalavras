#include "ProcuraMatriz.h"
#include <pthread.h>
#include <time.h>

clock_t processoContinuo();
clock_t pesquisaThreads();
void procuraPalavra(char **palavrasProcuradas);

void* f_thread(void *v);

int nroLinhas = 0, nroColunas = 0;
clock_t tempo = 0;
TLetra **texto = NULL;
char **palavrasProcuradas = NULL;

int main(){

    printf("\n############################################################################\n");
    printf(" #### Threads - Caca-palavras ####\n");
    printf("############################################################################\n\n");
    if(lerArquivo(&nroLinhas, &nroColunas, &palavrasProcuradas, &texto) == FALSE) {
        //se o arquivo não foi encontrado
        printf(" Problemas ao ler do arquivo\n");
        exit(-1);
    }

    tempo = processoContinuo();
    printf("\n\n ##Tempo de procura continua: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));
    printf("############################################################################\n\n");


    tempo = pesquisaThreads();
    printf("\n\n ##Tempo de procura com thread: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));
    printf("############################################################################\n\n");

    if(escreverArquivoSaida(nroLinhas, nroColunas, &texto) == FALSE){
        printf(" Erro, nao foi possivel criar o arquivo\n");
        exit(-1);
    }

    free(texto);
    free(palavrasProcuradas);

    return 1;
}

clock_t processoContinuo(){
    int i;
    clock_t tInicio, tFim;

    tInicio = clock();
    for(i = 0; i < NUMERO_PALAVRAS; i++){
        printf("***** PALAVRA %i ***** \n", i+1);
        procuraPalavra(&palavrasProcuradas[i]);
    }

    tFim = clock();
    return (tFim - tInicio);
}

clock_t pesquisaThreads(){
    //será criado uma thread para cada palavra
    pthread_t thr[NUMERO_PALAVRAS];
    clock_t tTempo = 0;
    clock_t retorno = 0;
    int i = 0;

    for(i = 0; i < NUMERO_PALAVRAS; i++){
       pthread_create(&thr[i], NULL, f_thread, (void*) &palavrasProcuradas[i]);
    }

    for(i = 0; i < NUMERO_PALAVRAS; i++){
        pthread_join(thr[i], (void*) &retorno);
        tTempo += retorno;
    }

    return tTempo;
}

void* f_thread(void *v) {
    clock_t tInicio, tFim, tTempo;

    tInicio = clock(); //tempo inicial
    procuraPalavra( (char**) v);
    tFim = clock(); //tempo final

    //calculo de tempo da thread
    tTempo = tFim - tInicio;

    //printf("\n tempo: %lf \n",(double) tTempo);
    pthread_exit((void**) tTempo);

    return NULL;
}

void procuraPalavra(char **palavrasProcuradas){

    if(procurarHorizontal(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarHorizontalInvertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarVertical(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarVerticalInvertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarDiagonal1(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarDiagonal1Invertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarDiagonal2(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }

    if(procurarDiagonal2Invertido(nroLinhas, nroColunas, &(*palavrasProcuradas), &texto) == ACHOU){
        return;
    }
}

