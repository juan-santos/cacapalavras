#include "ProcuraMatriz.h"
#include <time.h>

int main(){

    int nroLinhas = 0, nroColunas = 0;

    //declaro as strings
    TLetra **texto = NULL;
    char **palavrasProcuradas = NULL;
    int i;

    printf(" #### Threads - Caca-palavras ####");

    if(lerArquivo(&nroLinhas, &nroColunas, &palavrasProcuradas, &texto) == TRUE) {
        //se for possível ler o arquivo

        clock_t tInicio, tFim, tDecorrido;

        tInicio = clock();
        for(i = 0; i < NUMERO_PALAVRAS; i++){

            printf("\n\n Procurando por: %s\n", palavrasProcuradas[i]);

            if(procurarHorizontal(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarHorizontalInvertido(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarVertical(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarVerticalInvertido(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarDiagonal1(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarDiagonal1Invertido(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarDiagonal2(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }

            if(procurarDiagonal2Invertido(nroLinhas, nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf(" Nao foi encontrado\n");
            }
        }

        tFim = clock();
        tDecorrido = (tFim - tInicio);

        printf("\n##################\n");
        printf("# Tempo processo: %d \n",tDecorrido);
        printf("##################\n");
        printf("\n\n Escrevendo arquivo de saida...\n");


        /**/
        if(escreverArquivoSaida(nroLinhas, nroColunas, &texto) == FALSE){
            printf(" Erro, nao foi possivel criar o arquivo\n");
        }

    } else{
        //se o arquivo não foi encontrado
        printf(" Problemas ao ler do arquivo\n");
    }

    free(texto);
    free(palavrasProcuradas);

    return 1;
}
