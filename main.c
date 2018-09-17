#include "ProcuraMatriz.h"
#include <pthread.h>
#include <windows.h>
//#include <unistd.h>
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


    printf(" #### Threads - Caca-palavras ####");
    if(lerArquivo(&nroLinhas, &nroColunas, &palavrasProcuradas, &texto) == FALSE) {
        //se o arquivo n�o foi encontrado
        printf(" Problemas ao ler do arquivo\n");
        exit(-1);
    }

    tempo = processoContinuo();
    printf("\n\n ##Tempo continuo: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));

    printf("############################################################################\n");

    tempo = pesquisaThreads();
    printf("\n\n ##Tempo thread: %lf ms\n", (double)tempo / (CLOCKS_PER_SEC/1000));

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
        procuraPalavra(&palavrasProcuradas[i]);
    }

    tFim = clock();
    return (tFim - tInicio);
}

clock_t pesquisaThreads(){
    //ser� criado uma thread para cada palavra
    pthread_t thr[NUMERO_PALAVRAS];
    clock_t tInicio, tFim;
    int i = 0;

    tInicio = clock();
    for(i = 0; i < NUMERO_PALAVRAS; i++){
        //pthread_create(&thr[i], NULL, f_thread, (void*) i);
        //pthread_join(thr[i], NULL);

        procuraPalavra(&palavrasProcuradas[i]);
    }

    tFim = clock();
    return (tFim - tInicio);
}

void* f_thread(void *v) {
  int thr_id;
  Sleep(1);
  thr_id = *(int*) v;
  printf("Thread %d.\n", thr_id);
  return NULL;
}

void procuraPalavra(char **palavrasProcuradas){

   printf("\n\n Procurando por: %s\n", (*palavrasProcuradas));

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

