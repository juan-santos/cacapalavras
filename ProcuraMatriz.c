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


int horizontal(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao){
    int tamanhoPalavra = strlen(*palavraProcurada);
    int i = 0, j = 0, substring = 0;

    tamanhoPalavra = strlen(*palavraProcurada);

    for(i = 0; i < nroLinhas; i++){
        for(j = 0; j <= (nroColunas - tamanhoPalavra); j++){
            char aux[NUMERO_LETRAS+1] = "";

            //se as primeiras letras não baterem, nem perco tempo comparando
            if((*texto)[i][j].letra != (*palavraProcurada)[0]){
                continue;
            }

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
                    (*texto)[i][substring+j].cor = RED;
                    substring++;
                }

                if(direcao == SENTIDO_NORMAL){

                    printf("HORIZONTAL => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada,
                           (*texto)[i][j].coluna, (*texto)[i][j].linha, (*texto)[i][substring+j].coluna, (*texto)[i][substring+j].linha);
                } else{

                    printf("HORIZONTAL INVERTIDO => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada,
                           (*texto)[i][j].coluna, (*texto)[i][j].linha, (*texto)[i][substring+j].coluna, (*texto)[i][substring+j].linha);
                }

                return ACHOU;
            }
        }
    }

    if(direcao == SENTIDO_NORMAL){

        printf("HORIZONTAL => Nao encontrado: %s\n\n", *palavraProcurada);
    } else{

        printf("HORIZONTAL INVERTIDO => Nao encontrado: %s\n\n", *palavraProcurada);
    }

    return NAO_ACHOU;
}
int procurarHorizontal(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    return horizontal(nroLinhas, nroColunas, &(*palavraProcurada), &(*texto), SENTIDO_NORMAL);
}
int procurarHorizontalInvertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    int resultado;
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));
    resultado = horizontal(nroLinhas, nroColunas, &palavraInvertida, &(*texto), SENTIDO_INVERSO);
    free(palavraInvertida);
    return resultado;
}


int vertical(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao){
    int tamanhoPalavra = strlen(*palavraProcurada);
    int i = 0, j = 0, substring = 0;

    tamanhoPalavra = strlen(*palavraProcurada);

    for(j = 0; j < nroColunas; j++){
        for(i = 0; i <= (nroLinhas - tamanhoPalavra); i++){
            char aux[NUMERO_LETRAS+1] = "";

            //se as primeiras letras não baterem, nem perco tempo comparando o resto
            if((*texto)[i][j].letra != (*palavraProcurada)[0]){
                continue;
            }

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
                    (*texto)[substring+i][j].cor = GREEN;
                    substring++;
                }

                if(direcao == SENTIDO_NORMAL){
                    printf("VERTICAL => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada, (*texto)[i][j].coluna
                           , (*texto)[i][j].linha, (*texto)[substring+i][j].coluna, (*texto)[substring+i][j].linha);
                } else {
                    printf("VERTICAL INVERTIDO => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada
                           , (*texto)[i][j].coluna, (*texto)[i][j].linha, (*texto)[substring+i][j].coluna, (*texto)[substring+i][j].linha);
                }

                return ACHOU;
            }
        }
    }

    if(direcao == SENTIDO_NORMAL){
        printf("VERTICAL => Nao encontrado: %s\n\n", *palavraProcurada);
    } else{
        printf("VERTICAL INVERTIDO => Nao encontrado: %s\n\n", *palavraProcurada);
    }

    return NAO_ACHOU;
}
int procurarVertical(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    return vertical(nroLinhas, nroColunas, &(*palavraProcurada), &(*texto), SENTIDO_NORMAL);
}
int procurarVerticalInvertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    int resultado;
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));
    resultado = vertical(nroLinhas, nroColunas, &palavraInvertida, &(*texto), SENTIDO_INVERSO);
    free(palavraInvertida);
    return resultado;
}

int diagonal1(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao){
    int i, j, c, linha, coluna, nroLinhasDiagonal, nroColunasDiagonal, substring, tamanhoPalavra;
    //numero de diagonais existentes de acordo com a matriz dada
    nroLinhasDiagonal = (nroLinhas) + (nroColunas) - 1;

    //numero maximo de linhas na diagonal de acordo com a matriz dada
    nroColunasDiagonal = nroLinhas + 1;

    //tamanho da palavra dada
    tamanhoPalavra = strlen(*palavraProcurada);

    //Percorrendo todas as linhas formadas nas diagonais
    for(linha = 0; linha < nroLinhasDiagonal; linha++){

        //variavel auxiliar que armazena a diagonal da iteração
        TLetra *linhaDiagonal = (TLetra*) malloc (nroColunasDiagonal * sizeof(TLetra));

        //variavel auxiliar que armazena substrings da iteração
        char *aux = (char*) malloc ((tamanhoPalavra+1) * sizeof(char));

        //obtenho a string da diagonal iterada
        coluna = 0;

        if(linha < nroLinhas) {
            i = linha;
            j = 0;
        } else {
            i = nroLinhas - 1; //maior valor possivel da linha em uma matriz
            j = 1 + linha - nroLinhas;
        }

        while((i > -1) && (j < nroColunas)){
            linhaDiagonal[coluna].letra = (*texto)[i][j].letra;
            linhaDiagonal[coluna].linha = (*texto)[i][j].linha;
            linhaDiagonal[coluna].coluna = (*texto)[i][j].coluna;
            coluna++;
            i--;
            j++;
        }
        linhaDiagonal[coluna].letra = '\0';

        for(c = 0; c < nroColunasDiagonal; c++){

            //Se a primeira letra não bater realizo a busca da proxima substring
            if(linhaDiagonal[c].letra != (*palavraProcurada)[0]){
                continue;
            }

            substring = 0;
            while(substring < tamanhoPalavra){
                aux[substring] = linhaDiagonal[substring+c].letra;
                substring++;
            }
            aux[substring] = '\0';

            if(strcmp(aux,(*palavraProcurada)) == 0){

                substring = 0;
                while(substring < tamanhoPalavra){
                    (*texto)[linhaDiagonal[substring+c].linha][linhaDiagonal[substring+c].coluna].achou = ACHOU;
                    (*texto)[linhaDiagonal[substring+c].linha][linhaDiagonal[substring+c].coluna].cor = YELLOW;
                    substring++;
                }

                substring--;
                if(direcao == SENTIDO_NORMAL){
                    printf("DIAGONAL 1 => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada, linhaDiagonal[c].linha
                           , linhaDiagonal[c].coluna, linhaDiagonal[c + substring].linha, linhaDiagonal[c + substring].coluna);
                } else {
                    printf("DIAGONAL 1 INVERTIDO => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada, linhaDiagonal[c].linha
                           , linhaDiagonal[c].coluna, linhaDiagonal[c + substring].linha, linhaDiagonal[c + substring].coluna);
                }

                free(aux);
                return ACHOU;
            }

        }

        free(aux);
    }

    if(direcao == SENTIDO_NORMAL){
        printf("DIAGONAL 1 => Nao encontrado: %s\n\n", *palavraProcurada);
    } else{
        printf("DIAGONAL 1 INVERTIDO => Nao encontrado: %s\n\n", *palavraProcurada);
    }

    return NAO_ACHOU;
}
int procurarDiagonal1(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    return diagonal1(nroLinhas, nroColunas, &(*palavraProcurada), &(*texto), SENTIDO_NORMAL);
}
int procurarDiagonal1Invertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));
    return diagonal1(nroLinhas, nroColunas, &palavraInvertida, &(*texto), SENTIDO_INVERSO);
}

int diagonal2(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto, int direcao){
    int i, j, c, linha, coluna, nroLinhasDiagonal, nroColunasDiagonal, substring, tamanhoPalavra;
    //numero de diagonais existentes de acordo com a matriz dada
    nroLinhasDiagonal = (nroLinhas) + (nroColunas) - 1;

    //numero maximo de linhas na diagonal de acordo com a matriz dada
    nroColunasDiagonal = nroLinhas + 1;

    //tamanho da palavra dada
    tamanhoPalavra = strlen(*palavraProcurada);

    //Percorrendo todas as linhas formadas nas diagonais
    for(linha = 0; linha < nroLinhasDiagonal; linha++){

        //variavel auxiliar que armazena a diagonal da iteração
        TLetra *linhaDiagonal = (TLetra*) malloc (nroColunasDiagonal * sizeof(TLetra));

        //variavel auxiliar que armazena substrings da iteração
        char *aux = (char*) malloc ((tamanhoPalavra+1) * sizeof(char));

        //obtenho a string da diagonal iterada
        coluna = 0;

        if(linha < nroLinhas) {
            i = linha;
            j = nroColunas-1;
        } else {
            i = nroLinhas - 1; //maior valor possivel da linha em uma matriz
            j = nroColunas - linha - 1;
        }

        while((i > -1) && (j > -1)){
            linhaDiagonal[coluna].letra = (*texto)[i][j].letra;
            linhaDiagonal[coluna].linha = (*texto)[i][j].linha;
            linhaDiagonal[coluna].coluna = (*texto)[i][j].coluna;
            coluna++;
            i--;
            j--;
        }
        linhaDiagonal[coluna].letra = '\0';

        for(c = 0; c < nroColunasDiagonal; c++){

            if(linhaDiagonal[c].letra != (*palavraProcurada)[0]){
                continue;
            }

            substring = 0;
            while(substring < tamanhoPalavra){
                aux[substring] = linhaDiagonal[substring+c].letra;
                substring++;
            }
            aux[substring] = '\0';

            if(strcmp(aux,(*palavraProcurada)) == 0){

                substring = 0;
                while(substring < tamanhoPalavra){
                    (*texto)[linhaDiagonal[substring+c].linha][linhaDiagonal[substring+c].coluna].achou = ACHOU;
                    (*texto)[linhaDiagonal[substring+c].linha][linhaDiagonal[substring+c].coluna].cor = YELLOW;
                    substring++;
                }

                substring--;
                if(direcao == SENTIDO_NORMAL){
                    printf("DIAGONAL 2 => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada, linhaDiagonal[c].linha
                           , linhaDiagonal[c].coluna, linhaDiagonal[c+substring].linha, linhaDiagonal[c+substring].coluna);
                } else {
                    printf("DIAGONAL 2 INVERTIDO => ENCONTRADO '%s' inicio:(%i,%i), fim: (%i,%i) \n\n", *palavraProcurada, linhaDiagonal[c].linha
                           , linhaDiagonal[c].coluna, linhaDiagonal[c+substring].linha, linhaDiagonal[c+substring].coluna);
                }
                free(linhaDiagonal);
                return ACHOU;
            }
        }

        free(linhaDiagonal);
    }

    if(direcao == SENTIDO_NORMAL){
        printf("DIAGONAL 2 => Nao encontrado: %s\n\n", *palavraProcurada);
    } else{
        printf("DIAGONAL 2 INVERTIDO => Nao encontrado: %s\n\n", *palavraProcurada);
    }

    return NAO_ACHOU;
}
int procurarDiagonal2(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    return diagonal2(nroLinhas, nroColunas, &(*palavraProcurada), &(*texto), SENTIDO_NORMAL);
}
int procurarDiagonal2Invertido(int nroLinhas, int nroColunas, char **palavraProcurada, TLetra ***texto){
    char *palavraInvertida = (char*) malloc(NUMERO_LETRAS + 1 * sizeof(char));
    inverter(&(*palavraProcurada), &(palavraInvertida));
    return diagonal2(nroLinhas, nroColunas, &palavraInvertida, &(*texto), SENTIDO_INVERSO);
}

int lerArquivo(int *nroLinhas, int *nroColunas, char ***palavasProcuradas, TLetra ***texto){
    FILE *arq;
    arq = fopen("texto.txt", "r");

    if (arq != NULL){
        int i, j;
        char c;
        //Obtenho a quantidade de linhas e colunas
        fscanf(arq,"%i %i\n", nroLinhas, nroColunas);

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
                    (*texto)[i][j].cor = BLACK;
                    (*texto)[i][j].achou = FALSE;
                    (*texto)[i][j].linha = i;
                    (*texto)[i][j].coluna = j;
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
int escreverArquivoSaida(int nroLinhas, int nroColunas, TLetra ***texto){
    FILE *arq;
	arq = fopen("saida.txt", "w");

	if(arq == NULL){
        return FALSE;
	}
	else{

        int i,j;
        for(i = 0; i < nroLinhas; i++){
            printf(" ");
            for(j = 0; j < nroColunas; j++){

                if(((*texto)[i][j].achou == TRUE) &&
                   ((*texto)[i][j].letra > 96) &&
                   ((*texto)[i][j].letra < 123))
                {
                    (*texto)[i][j].letra = (*texto)[i][j].letra - 32;
                    textcolor((*texto)[i][j].cor);
                }

                fputc((*texto)[i][j].letra, arq);
                printf("%c", (*texto)[i][j].letra);
                textcolor(WHITE);
            }

            fputc('\n', arq);
            printf("\n");
        }
        textcolor(WHITE);
		fclose(arq);
	}

	return TRUE;
}
