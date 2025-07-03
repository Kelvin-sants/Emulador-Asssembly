//ARQUIVO COM AS FUNCOES RESPONSAVEIS POR LER O ASSEMBLY ENVIADO PELO USUARIO,
//TRADUZIR PARA LINGUAGEM DE MAQUINA E GUARDAR A TRADUCAO NA MEMORIA DO EMULADOR

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "LerAssembly.h"

#define TAM_MAX_ASSEMBLY 1000
#define TAM_LINHA 20
#define TRUE 1
#define FALSE 0

void limparBufferEntrada() {                        //funcao para limpar o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int linha_vazia(const char *str) {                                  //funcao para verificar se o Emulador recebeu uma linha vazia
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace((unsigned char)str[i])) {
            return 0; // tem algum caractere que não é espaço
        }
    }
    return 1; // só espaços ou vazio
}

char* lerAssemblyTerminal(char* entrada){                   //funcao para ler o Assembly no terminal

    int continuarLeitura = 1;
    int numLinhaTerminal = 1;

    limparBufferEntrada();                 //limpa o buffer de entrada
    
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

// Função para ler código passado por um arquivo
char* lerAssemblyArquivo(const char* nomeArquivo, char* destino) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo '%s'. Certifique-se de que ele existe.\n", nomeArquivo);
        return NULL;
    }

    char linha[TAM_LINHA];
    destino[0] = '\0';

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        strcat(destino, linha);
    }

    fclose(arquivo);
    return destino;
}


char** separarCodigoAssembly(char* entrada, int *qtdPalavras) {          //faz um vetor de ponteiros onde cada ponteiro aponta para uma palavra da entrada


    char **codigoAssembly = (char**) malloc(300 * sizeof(char*));       //reserva espaço para um vetor de ponteiros char

    if (codigoAssembly != NULL) {                                       //se conseguiu alocar
       
        int i = 0;
        char *token = strtok(entrada, " \n");                           //pega a primeira palavra até o primeiro espaço
    
        while (token != NULL && i < 300) {                              //se a palavra for válida
            codigoAssembly[i] = token;                                  //armazena a palavra
            i++;
            token = strtok(NULL, " \n");                                //pega a proxima palavra
        }
        while(i < 300){                                                 //se sobrar espaços no vetor
            codigoAssembly[i] = NULL;                                   //preenche os espaços com NULL
            i++;
        }
    
        *qtdPalavras = i;                                               //atualiza a quantidade de palavras                     
        return codigoAssembly;                                          //retorna o vetor de palavras
    }
    return NULL;
}

int devolveRegistrador(char* registrador) {             //devolve o registrador de acordo com o nome passado
    if (registrador == NULL) return -1;

    // Verifica se começa com 'R'
    if (registrador[0] != 'R') return -1;

    // Converte o restante para número
    int num = atoi(&registrador[1]);

    // Aceita apenas R1 até R8
    if (num >= 1 && num <= 8) {
        return num - 1;  // R1 → 0, R8 → 7
    }

    return -1; // Registrador inválido
}


int argumentosSuficientes(char** codigoAssembly, int pos, int total, int esperados) {           //verifica se a instrução passada tem argumentos o suficiente

    if ((pos + esperados) > total){                             //se os argumentos forem insulficientes
        return FALSE;                                           //retorna FALSE
    }
    for (int j = 1; j <= esperados; j++) {                      //se algum argumento for invalido
        if (codigoAssembly[pos + j] == NULL){
            return FALSE;                                       //retorna FALSE
        }
    }
    return TRUE;                                                //caso passe pelas verificações retorna TRUE
}

void traduzParaLinguagemDeMaquina(char** codigoAssembly, int* memoria, int quantPalavras, int *ultimaPosMemoria) {          //funcao responsavel por traduzir o código assembly para
    int continuar = TRUE;                                                                                                   //linguagem de maquina e colocar o resultado na memoria
    int i = 0;  // posição no vetor de palavras do código Assembly
    int k = *ultimaPosMemoria;  // próxima posição livre na memória
    char* palavra;

    while (continuar) {
        if (i >= quantPalavras || codigoAssembly[i] == NULL) {
            break;
        }

        palavra = codigoAssembly[i];

        // Instrução LOAD
        if (strcmp(palavra, "LOAD") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 2)) {
                printf("Erro: LOAD espera 2 argumentos (registrador, endereco).\n");
                break;
            }
            int reg = devolveRegistrador(codigoAssembly[i+1]);
            if (reg == -1) {
                printf("Erro: Registrador invalido '%s'.\n", codigoAssembly[i+1]);
                break;
            }
            memoria[k] = 1;
            memoria[k+1] = reg;
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        // Instrução STORE
        else if (strcmp(palavra, "STORE") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 2)) {
                printf("Erro: STORE espera 2 argumentos (registrador, endereco).\n");
                break;
            }
            int reg = devolveRegistrador(codigoAssembly[i+1]);
            if (reg == -1) {
                printf("Erro: Registrador invalido '%s'.\n", codigoAssembly[i+1]);
                break;
            }
            memoria[k] = 2;
            memoria[k+1] = reg;
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        // Instrução ADD
        else if (strcmp(palavra, "ADD") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 3)) {
                printf("Erro: ADD espera 3 registradores.\n");
                break;
            }
            int reg1 = devolveRegistrador(codigoAssembly[i+1]);
            int reg2 = devolveRegistrador(codigoAssembly[i+2]);
            int reg3 = devolveRegistrador(codigoAssembly[i+3]);

            if (reg1 == -1 || reg2 == -1 || reg3 == -1) {
                printf("Erro: Registrador invalido em ADD.\n");
                break;
            }
            memoria[k] = 3;
            memoria[k+1] = reg1;
            memoria[k+2] = reg2;
            memoria[k+3] = reg3;
            k += 4;
            i += 4;
        }

        // Instrução SUB
        else if (strcmp(palavra, "SUB") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 3)) {
                printf("Erro: SUB espera 3 registradores.\n");
                break;
            }
            int reg1 = devolveRegistrador(codigoAssembly[i+1]);
            int reg2 = devolveRegistrador(codigoAssembly[i+2]);
            int reg3 = devolveRegistrador(codigoAssembly[i+3]);

            if (reg1 == -1 || reg2 == -1 || reg3 == -1) {
                printf("Erro: Registrador invalido em SUB.\n");
                break;
            }
            memoria[k] = 4;
            memoria[k+1] = reg1;
            memoria[k+2] = reg2;
            memoria[k+3] = reg3;
            k += 4;
            i += 4;
        }

        // Instrução LOADI
        else if (strcmp(palavra, "LOADI") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 2)) {
                printf("Erro: LOADI espera 2 argumentos (registrador, valor).\n");
                break;
            }
            int reg = devolveRegistrador(codigoAssembly[i+1]);
            if (reg == -1) {
                printf("Erro: Registrador invalido '%s'.\n", codigoAssembly[i+1]);
                break;
            }
            memoria[k] = 5;
            memoria[k+1] = reg;
            memoria[k+2] = atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            k += 4;
            i += 3;
        }

        // Instrução JUMP
        else if (strcmp(palavra, "JUMP") == 0) {
            if (!argumentosSuficientes(codigoAssembly, i, quantPalavras, 1)) {
                printf("Erro: JUMP espera 1 argumento (endereco).\n");
                break;
            }
            memoria[k] = 6;
            memoria[k+1] = atoi(codigoAssembly[i+1]);
            memoria[k+2] = 0;
            memoria[k+3] = 0;
            k += 4;
            i += 2;
        }

        // Instrução HALT
        else if (strcmp(palavra, "HALT") == 0) {
            memoria[k] = 7;
            memoria[k+1] = 0;
            memoria[k+2] = 0;
            memoria[k+3] = 0;
            continuar = FALSE;
            k += 4;
        }

        // Instrução desconhecida
        else {
            printf("Erro: Instrucao desconhecida '%s'\n", palavra);
            break;
        }
    }

    *ultimaPosMemoria = k;  // atualiza a posição final da memória ocupada
}
