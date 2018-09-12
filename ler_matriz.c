#include <stdlib.h>
#include "ProcuraMatriz.h"

int escreverArquivoSaida(int *nroLinhas, int *nroColunas, TLetra ***texto);
int lerArquivo(int *nroLinhas, int *nroColunas, char ***palavasProcuradas, TLetra ***texto);

int main(){

    int nroLinhas = 0, nroColunas = 0;

    //declaro as strings
    TLetra **texto = NULL;
    char **palavrasProcuradas = NULL;
    int i;

    printf("#### Threads - Caca-palavras ####");

    if(lerArquivo(&nroLinhas, &nroColunas, &palavrasProcuradas, &texto) == TRUE) {
        //se for possível ler o arquivo

        for(i = 0; i < NUMERO_PALAVRAS; i++){

            printf("\n\nProcurando por: %s\n", palavrasProcuradas[i]);

            if(procurarHorizontal(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarHorizontalInvertido(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarVertical(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarVerticalInvertido(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarDiagonal1(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarDiagonal1Invertido(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarDiagonal2(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }

            if(procurarDiagonal2Invertido(&nroLinhas, &nroColunas, &palavrasProcuradas[i], &texto) == ACHOU){
                continue;
            } else{
                 printf("Nao foi encontrado\n");
            }
        }

        printf("\n\nEscrevendo arquivo de saida...\n");
        system("PAUSE");
        printf("\n\n");

        /**/
        if(escreverArquivoSaida(&nroLinhas, &nroColunas, &texto) == FALSE){
            printf("Erro, nao foi possivel criar o arquivo\n");
        }

    } else{
        //se o arquivo não foi encontrado
        printf("Problemas ao ler do arquivo\n");
    }

    free(texto);
    free(palavrasProcuradas);

    //para o programa não fechar imediatamente
    printf("\n\nEncerrando o programa\n");
    system("PAUSE");
    return 1;
}

int lerArquivo(int *nroLinhas, int *nroColunas, char ***palavasProcuradas, TLetra ***texto){
    FILE *arq;
    arq = fopen("texto.txt", "r");

    if (arq != NULL){
        int i, j;
        char c;
        //Obtenho a quantidade de linhas e colunas
        fscanf(arq,"%i %i\n", nroLinhas, nroColunas);

        //(*nroLinhas)++;

        //aloco dinamicamente as colunas da matriz
        *texto = (TLetra**) malloc(*nroLinhas * sizeof(TLetra*));

        for(i = 0; i < *nroLinhas; i++){
            int fimLinha = FALSE;
            //alocação da matriz
            (*texto)[i] = (TLetra*) malloc((*nroColunas) * sizeof(TLetra));

            //iniciando a matriz com valores padrões
            for(j = 0; j <= *nroColunas; j++){

                if(fimLinha == FALSE){
                    //se NÃO for final de linha
                    c = fgetc(arq);

                    if(c != '\n' && c != EOF){
                        (*texto)[i][j].letra = c;
                    }

                } else{
                    //se for final de linha
                    (*texto)[i][j].letra = '\0';
                }

                if (j < *nroColunas){
                    (*texto)[i][j].cor = PRETO;
                    (*texto)[i][j].achou = FALSE;
                }
            }
        }

        //aloco dinânicamente as linhas da matriz
        *palavasProcuradas = (char**) malloc(NUMERO_PALAVRAS * sizeof(char*));

        for(i = 0; i < NUMERO_PALAVRAS; i++){
            //alocação do espaço dinâmicco
            (*palavasProcuradas)[i] = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));

            j = 0;
            //enquanto estiver na mesma linha
            while( ((c = fgetc(arq)) != '\n') && c != EOF){
                (*palavasProcuradas)[i][j] = c;
                j++;
            }
            (*palavasProcuradas)[i][j] = '\0';
        }

        fclose(arq);
        return TRUE;
    }

    fclose(arq);
    return FALSE;
}

int escreverArquivoSaida(int *nroLinhas, int *nroColunas, TLetra ***texto){
    FILE *arq;
	arq = fopen("saida.txt", "w");

	if(arq == NULL){
        return FALSE;
	}
	else{

        int i,j;
        for(i = 0; i < *nroLinhas; i++){
            for(j = 0; j < *nroColunas; j++){

                if(((*texto)[i][j].achou == TRUE) &&
                   ((*texto)[i][j].letra > 96) &&
                   ((*texto)[i][j].letra < 123))
                {
                    (*texto)[i][j].letra = (*texto)[i][j].letra - 32;
                    textcolor(RED);
                }

                fputc((*texto)[i][j].letra, arq);
                printf("%c", (*texto)[i][j].letra);
                textcolor(WHITE);
            }
            fputc('\n', arq);
            printf("\n");
        }


		fclose(arq);
	}

	return TRUE;
}
