//ARQUIVO COM AS FUNCOES RESPONSAVEIS POR LER O ASSEMBLY ENVIADO PELO USUARIO,
//TRADUZIR PARA LINGUAGEM DE MAQUINA E GUARDAR A TRADUCAO NA MEMORIA DO EMULADOR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TAM_MAX_ASSEMBLY 1000
#define TAM_LINHA 20
#define TRUE 1
#define FALSE 0

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int linha_vazia(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0; // tem algum caractere que não é espaço
        }
    }
    return 1; // só espaços ou vazio
}

char* lerAssemblyTerminal(char* entrada){

    int continuarLeitura = 1;
    int numLinhaTerminal = 1;

    limparBufferEntrada();
    
    while(continuarLeitura){               //LENDO A ENTRADA DO USUARIO
        
        char linha[TAM_LINHA];

        printf("Linha %d:  ", numLinhaTerminal);

        fgets(linha, sizeof(linha), stdin);         //lê uma linha

        if (linha_vazia(linha)){      // Se o usuário apertar ENTER sem digitar nada, saímos do loop
            continuarLeitura = FALSE;
        }

        strcat(entrada, linha);  // concatena a linha lida ao texto total
        numLinhaTerminal++;
    }
    return entrada;             //retorna um vetor char com o codigo assembly escrito (tudo junto)
}

char** separarCodigoAssembly(char* entrada, int *qtdPalavras) {          //faz um vetor de ponteiros onde cada ponteiro aponta para uma palavra da entrada


    char **codigoAssembly = (char**) malloc(300 * sizeof(char*));
    if (codigoAssembly != NULL) {
       
        int i = 0;
        char *token = strtok(entrada, " \n");
    
        while (token != NULL && i < 300) {
            codigoAssembly[i] = token;
            i++;
            token = strtok(NULL, " \n");
        }
        while(i < 300){
            codigoAssembly[i] = NULL;
            i++;
        }
    
        *qtdPalavras = i;
        return codigoAssembly;
    }
    return NULL;
}

int devolveRegistrador(char* registrador){

    if (strcmp(registrador, "R1") == 0) return 0;
    if (strcmp(registrador, "R2") == 0) return 1;
    if (strcmp(registrador, "R3") == 0) return 2;
    if (strcmp(registrador, "R4") == 0) return 3;
    if (strcmp(registrador, "R5") == 0) return 4;
    if (strcmp(registrador, "R6") == 0) return 5;
    if (strcmp(registrador, "R7") == 0) return 6;
    if (strcmp(registrador, "R8") == 0) return 7;

    return -1;
}

int argumentosSuficientes(char** codigoAssembly, int pos, int total, int esperados) {

    if ((pos + esperados) > total){
        return FALSE;
    }
    for (int j = 1; j <= esperados; j++) {
        if (codigoAssembly[pos + j] == NULL){
            return FALSE;
        }
    }
    return TRUE;
}

void traduzParaLinguagemDeMaquina(char** codigoAssembly, int* memoria, int quantPalavras, int *ultimaPosMemoria) {

    int continuar = TRUE;
    int i = 0;  // posição no assembly
    int k = *ultimaPosMemoria;  // posição na memória
    char* palavra;
    

    
    while (continuar) {
        if (i >= quantPalavras) {
            continuar = FALSE;
            break;
        }

        palavra = codigoAssembly[i];
        if (palavra == NULL) {
            continuar = FALSE;
            break;
        }

        if (strcmp(palavra, "LOAD") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 2)) {
                printf("Erro: LOAD espera 2 argumentos (registrador, endereço).\n");
                break;
            }
            memoria[k] = 1;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        else if (strcmp(palavra, "STORE") == 0) {
            if (!argumentosSuficientes(codigoAssembly,i, quantPalavras, 2)) {
                printf("Erro: STORE espera 2 argumentos (registrador, endereço).\n");
                break;
            }
            memoria[k] = 2;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        else if (strcmp(palavra, "ADD") == 0) {
            if (!argumentosSuficientes(codigoAssembly,i, quantPalavras, 3)) {
                printf("Erro: ADD espera 3 registradores.\n");
                break;
            }
            memoria[k] = 3;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = devolveRegistrador(codigoAssembly[i+2]);
            memoria[k+3] = devolveRegistrador(codigoAssembly[i+3]);
            k += 4;
            i += 4;
        }

        else if (strcmp(palavra, "SUB") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 3)) {
                printf("Erro: SUB espera 3 registradores.\n");
                break;
            }
            memoria[k] = 4;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = devolveRegistrador(codigoAssembly[i+2]);
            memoria[k+3] = devolveRegistrador(codigoAssembly[i+3]);
            k += 4;
            i += 4;
        }

        else if (strcmp(palavra, "LOADI") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 2)) {
                printf("Erro: LOADI espera 2 argumentos (registrador, valor).\n");
                break;
            }
            memoria[k] = 5;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        else if (strcmp(palavra, "JUMP") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 1)) {
                printf("Erro: JUMP espera 1 argumento (endereço).\n");
                break;
            }
            memoria[k] = 6;
            memoria[k+1] = atoi(codigoAssembly[i+1]);
            memoria[k+2] = 0;
            memoria[k+3] = 0;

            k += 4;
            i += 2;
        }

        else if (strcmp(palavra, "HALT") == 0) {
            memoria[k] = 7;
            memoria[k+1] = 0;
            memoria[k+2] = 0;
            memoria[k+3] = 0;
            continuar = FALSE;
            k += 4;
            
        }

        else {
            printf("Erro: Instrucao desconhecida '%s'\n", palavra);
            continuar = FALSE;
        }
    }
    *ultimaPosMemoria = k;
}