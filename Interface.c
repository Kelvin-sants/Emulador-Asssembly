//ARQUIVO COM AS FUNCOES RESPONSAVEIS PELA INTERFACE (NO TERMINAL) DO EMULADOR

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TRUE 1
#define FALSE 0
#define TAM_MEMORIA 512
#define N_registradores 8
#define TAM_ENTRADA  300

void interfaceCPU(int* registradores, int PC, int flagZero, int registradorInstrucao){

    printf("\nINFORMACOES DO EMULADOR:\n");

    printf("\n------------------------------------------------------------------------------------------\n\n");

    printf("R1: %d \t\t\t\t\t R2: %d\n", registradores[0], registradores[1]);
    printf("R3: %d \t\t\t\t\t R4: %d\n", registradores[2], registradores[3]);
    printf("R5: %d \t\t\t\t\t R6: %d\n", registradores[4], registradores[5]);
    printf("R7: %d \t\t\t\t\t R8: %d\n", registradores[6], registradores[7]);
    printf("\n");
    printf("PC: %d \t\t\t\t\t IR: %d\n", PC+1, registradorInstrucao);
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

void mostrarInstrucoesAssembly(){

    printf("Instrucoes disponiveis:\n\n");
    printf("1 - LOAD (REGISTRADOR) (POS.MEMORIA)\n");
    printf("2 - STORE (REGISTRADOR) (POS.MEMORIA)\n");
    printf("3 - ADD (REGISTRADOR) (REGISTRADOR) (REGISTRADOR RESULTADO)\n");
    printf("4 - SUB (REGISTRADOR) (REGISTRADOR) (REGISTRADOR RESULTADO)\n");
    printf("5 - LOADI (REGISTRADOR) (VALOR INTEIRO)\n");
    printf("6 - JUMP (NUM.INSTRUCOES.PULAR)\n");
    printf("7 - HALT\n");
}

void mostrarOpcoesMenuPrincipal(){
    printf("Menu opcoes Emulador Assembly:\n\n");
    printf("1 - Mostrar interface CPU\n");          //
    printf("2 - Mostrar interface Linhas da Memoria\n");        //
    printf("3 - Mostrar interface Bytes da Memoria\n");          //
    printf("4 - Mostrar intrucoes do Emulador Assembly\n");      //
    printf("5 - Escrever um codigo Assembly e colocar na memoria\n");    //
    printf("6 - Executar o codigo Assembly na memoria\n");          //
    printf("7 - Reiniciar estado do Emulador Assembly\n");          //
    printf("8 - Continuar estado atual do Emulador Assembly\n");
    printf("9 - Mostrar Opcoes Menu Principal\n");          //
    printf("10 - Encerrar Emulador Assembly\n");         //
}
