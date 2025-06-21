//ARQUIVO COM AS FUNCOES DO PASSO 1:  Ler o código em assembly passado pelo usuário e guarda na memoria como "binário";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX_ASSEMBLY 1000
#define TRUE 1
#define FALSE 0

char* lerAssemblyTerminal(char* entrada){

    int continuar = 1;
    int numLinhaTerminal = 1;
    
    printf("Digite o codigo em Assembly:\nExemplo: ADD 10 R4\n");
    printf("(por ultimo uma linha em branco)\n\n");
    
    while(continuar){               //LENDO A ENTRADA DO USUARIO
        
        char linha[50];

        printf("Linha %d:  ", numLinhaTerminal);

        fgets(linha, sizeof(linha), stdin);         //lê uma linha

        if (strcmp(linha, "\n") == 0){      // Se o usuário apertar ENTER sem digitar nada, saímos do loop
            continuar = FALSE;
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

void traduzParaLinguagemDeMaquina(char** codigoAssembly, int* memoria){

    int continuar = TRUE;
    int i = 0;      //posicao no assembly
    int k = 0;      //posicao na memoria
    char* palavra;

    while(continuar){

        palavra = codigoAssembly[i];            // pega a i-ésima palavra


        if (strcmp(palavra, "LOAD") == 0){             //SE FOR ADD
            memoria[k] = 1;                                                     //instrucao opcode
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);             //registrador
            memoria[k+2] = atoi(codigoAssembly[i+2]);                           //valor da memoria
            memoria[k+3] = 0;

            k += 4;          //avanca 4 casas na memoria
            i += 3;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "STORE") == 0){             //SE FOR STORE
            memoria[k] = 2;
            memoria[k+1] =  devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] =  atoi(codigoAssembly[i+2]);
            memoria[k+3] = 0;
            
            k += 4;          //avanca 4 casas na memoria
            i += 3;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "ADD") == 0){
            memoria[k] = 3;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = devolveRegistrador(codigoAssembly[i+2]);
            memoria[k+3] = devolveRegistrador(codigoAssembly[i+3]);
            
            k += 4;          //avanca 4 casas na memoria
            i += 4;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "SUB") == 0){
            memoria[k] = 4;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = devolveRegistrador(codigoAssembly[i+2]);
            memoria[k+3] = devolveRegistrador(codigoAssembly[i+3]);
            
            k += 4;          //avanca 4 casas na memoria
            i += 4;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "LOADI") == 0){
            memoria[k] = 5;
            memoria[k+1] = devolveRegistrador(codigoAssembly[i+1]);
            memoria[k+2] = atoi(codigoAssembly[i+2]); 
            memoria[k+3] = 0;
            
            k += 4;          //avanca 4 casas na memoria
            i += 3;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "JUMP") == 0){
            memoria[k] = 6;
            memoria[k+1] = atoi(codigoAssembly[i+1]);
            memoria[k+2] = 0; 
            memoria[k+3] = 0;
            
            k += 4;          //avanca 4 casas na memoria
            i += 2;          //pega o proximo codigo em assembly
        }


        if (strcmp(palavra, "HALT") == 0){
            memoria[k] = 8;
            memoria[k+1] = 0;
            memoria[k+2] = 0; 
            memoria[k+3] = 0;
            
            k += 4;          //avanca 4 casas na memoria
            i += 1;          //pega o proximo codigo em assembly
        }
    }
}