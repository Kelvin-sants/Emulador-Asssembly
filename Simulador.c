#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TAM_MEMORIA 512
#define N_registradores 8

void inicializar(int* registradores, int* memoria, int* PC){                 //funcao para inicializar todos os registradores e espacos de memoria como 0;

    for (int i = 0; i < N_registradores; i++) {
        registradores[i] = 0;
    }

    for (int i = 0; i < TAM_MEMORIA; i++) {
        memoria[i] = 0;
    }

    *PC = 0;
}

void interfaceCPU(int* registradores, int PC, int flagZero, int registradorInstrucao){

    printf("\nINFORMACOES DO EMULADOR:\n");

    printf("\n------------------------------------------------------------------------------------------\n\n");

    printf("R1: %d \t\t\t\t\t R2: %d\n", registradores[0], registradores[1]);
    printf("R3: %d \t\t\t\t\t R4: %d\n", registradores[2], registradores[3]);
    printf("R5: %d \t\t\t\t\t R6: %d\n", registradores[4], registradores[5]);
    printf("R7: %d \t\t\t\t\t R8: %d\n", registradores[6], registradores[7]);
    printf("\n");
    printf("PC: %d \t\t\t\t\t IR: %d\n", PC, registradorInstrucao);
    printf("\n");
    printf("Registrador Flag Zero: %d\n", flagZero);

    printf("\n------------------------------------------------------------------------------------------\n\n");
  
}

void interfaceMemoriaBytes(int* memoria){

    printf("\nBYTES EM CADA POSICAO DE MEMORIA:\n\n");
    int i = 0;
    int contLinha;
    int numByte = 1;
    int numLinhas = TAM_MEMORIA / 4;
    for(contLinha = 0; contLinha < numLinhas; contLinha++){
        
        printf("BYTE %d: %d         BYTE %d: %d         BYTE %d: %d         BYTE %d: %d\n", numByte, memoria[i], numByte + 1, memoria[i+1], numByte + 2, memoria[i+2], numByte + 3, memoria[i+3]);
        numByte += 4;
        i +=  4;
    }

}

void interfaceMemoriaLinha(int* memoria){

    printf("\nLINHAS NA MEMORIA:\n\n");

    int contLinha;
    int i = 0;
    int num_Linhas = TAM_MEMORIA/ 4;
    for(contLinha = 1; contLinha <= num_Linhas; contLinha++){
        
        printf("Linha %d:   %d  %d  %d  %d\n", contLinha, memoria[i], memoria[i+1], memoria[i+2], memoria[i+3]);
        i += 4;
    }
}

void limparTerminal(){
    system("cls");
}

int main(){                 //APENAS PARA TESTES

    int registradores[N_registradores];       //R0 R1 R2 R3 R4 R5 R6 R7- registradores de uso geral
    int PC;                     //guarda o endereço da proxima instrucao
    int memoria[TAM_MEMORIA];           //memoria principal tanto pra dados quanto pra código
    int flagZero = 0;                   // resultado de comparação foi zero?
    int registradorInstrucao = 0;       //armazena a instrucao atual sendo executada

    inicializar(registradores, memoria, &PC);

    limparTerminal();
    interfaceCPU(registradores, PC, flagZero, registradorInstrucao);
    sleep(2);
    limparTerminal();
    interfaceMemoriaLinha(memoria);
    sleep(2);
    limparTerminal();
    interfaceMemoriaBytes(memoria);
}