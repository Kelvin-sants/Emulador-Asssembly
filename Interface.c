//ARQUIVO COM AS FUNCOES RESPONSAVEIS PELA INTERFACE (NO TERMINAL) DO EMULADOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Interface.h"

#define TRUE 1
#define FALSE 0
#define TAM_MEMORIA 512
#define N_registradores 8
#define TAM_ENTRADA  300

void interfaceCPU(int* registradores, int PC, int flagZero, int registradorInstrucao){
    printf("\n+--------------------[ EMULADOR ASSEMBLY - CPU STATE ]--------------------+\n");
    printf("| PC: %03d | IR: %03d | Flag Zero: %d                                        |\n", PC + 1, registradorInstrucao, flagZero);
    printf("|-------------------------------------------------------------------------|\n");
    printf("| R1: %03d | R2: %03d | R3: %03d | R4: %03d                                   |\n", registradores[0], registradores[1], registradores[2], registradores[3]);
    printf("| R5: %03d | R6: %03d | R7: %03d | R8: %03d                                   |\n", registradores[4], registradores[5], registradores[6], registradores[7]);
    printf("+-------------------------------------------------------------------------+\n");
}

void interfaceMemoriaBytes(int* memoria){

    printf("\n+--------------------[ MEMORIA - BYTES ]--------------------+\n\n");;
    int i = 0;
    int contLinha;
    int numByte = 1;
    int numLinhas = TAM_MEMORIA / 4;
    for(contLinha = 0; contLinha < numLinhas; contLinha++){
        printf("BYTE %03d: %03d  BYTE %03d: %03d  BYTE %03d: %03d  BYTE %03d: %03d\n", numByte, memoria[i], numByte + 1, memoria[i+1], numByte + 2, memoria[i+2], numByte + 3, memoria[i+3]);
        numByte += 4;
        i +=  4;
    }
    printf("+-----------------------------------------------------------+\n");
}

void interfaceMemoriaLinha(int* memoria){

    printf("\n+--------------------[ MEMORIA - LINHAS ]--------------------+\n\n");

    int contLinha;
    int i = 0;
    int num_Linhas = TAM_MEMORIA/ 4;
    for(contLinha = 1; contLinha <= num_Linhas; contLinha++){
        printf("Linha %03d:   %03d  %03d  %03d  %03d\n", contLinha, memoria[i], memoria[i+1], memoria[i+2], memoria[i+3]);
        i += 4;
    }
    printf("+-----------------------------------------------------------+\n");
}

void limparTerminal(){
    system("cls");
}

void mostrarInstrucoesAssembly(){
    printf("\n+--------------------[ INSTRUCOES DISPONIVEIS ]--------------------+\n");
    printf("| 1 - LOAD  (REG, ENDERECO)                                        |\n");
    printf("| 2 - STORE (REG, ENDERECO)                                        |\n");
    printf("| 3 - ADD   (REG1, REG2, REG_DESTINO)                              |\n");
    printf("| 4 - SUB   (REG1, REG2, REG_DESTINO)                              |\n");
    printf("| 5 - LOADI (REG, VALOR)                                           |\n");
    printf("| 6 - JUMP  (QUANTIDADE_INSTRUCOES)                                |\n");
    printf("| 7 - HALT                                                         |\n");
    printf("+------------------------------------------------------------------+\n");
}

void mostrarOpcoesMenuPrincipal(){
    printf("\n+-------------------[ MENU EMULADOR ASSEMBLY ]-------------------+\n");
    printf("| 1 - Mostrar interface CPU                                      |\n");
    printf("| 2 - Mostrar interface Linhas da Memoria                        |\n");
    printf("| 3 - Mostrar interface Bytes da Memoria                         |\n");
    printf("| 4 - Mostrar instrucoes do Emulador Assembly                    |\n");
    printf("| 5 - Escrever um codigo Assembly e colocar na memoria           |\n");
    printf("| 6 - Executar o codigo Assembly na memoria                      |\n");
    printf("| 7 - Reiniciar estado do Emulador Assembly                      |\n");
    printf("| 8 - Continuar estado atual do Emulador Assembly                |\n");
    printf("| 9 - Carregar codigo Assembly por um arquivo                    |\n");
    printf("|10 - Encerrar Emulador Assembly                                 |\n");
    printf("+----------------------------------------------------------------+\n");
}

