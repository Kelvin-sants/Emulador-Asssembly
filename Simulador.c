#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "LerAssembly.h"
#include "ExecutarAssembly.h"
#include "Interface.h"

// Variáveis da Arquitetura
#define TAM_MEMORIA 512
#define N_registradores 8
#define TAM_ENTRADA  300
#define TRUE 1
#define FALSE 0

// Colocar iniicializar e aguardar enter em interface.c
void inicializar(int* registradores, int* memoria, int* PC, int* flagZero, int* registradorInstrucao){                 //funcao para inicializar todos os registradores e espacos de memoria como 0;

    for (int i = 0; i < N_registradores; i++) {
        registradores[i] = 0;
    }

    for (int i = 0; i < TAM_MEMORIA; i++) {
        memoria[i] = 0;
    }

    *PC = 0;
    *flagZero = 0;
    *registradorInstrucao = 0;
}

void aguardarEnter() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

int main(){                 //APENAS PARA TESTES
    
    int registradores[N_registradores];       //R0 R1 R2 R3 R4 R5 R6 R7- registradores de uso geral
    int PC;                     //guarda o endereço da proxima instrucao
    int memoria[TAM_MEMORIA];           //memoria principal tanto pra dados quanto pra código
    int flagZero;                   // resultado de comparação foi zero?
    int registradorInstrucao;       //armazena a instrucao atual sendo executada

    int opcaoMenuPrincipal;
    int continuar = TRUE;
    char entrada[TAM_ENTRADA] = "";
    int quantPalavras = 0;
    char** codigoAssembly;
    int ultimaPosMemoria = 0;
    int status;
    
    inicializar(registradores, memoria, &PC, &flagZero, &registradorInstrucao);               //inicializa tudo como 0;

    limparTerminal();
    printf("+-------------------------------------------------------------+\n");
    printf("|         BEM-VINDO AO EMULADOR DE ASSEMBLY 8-BIT             |\n");
    printf("+-------------------------------------------------------------+\n\n");

    while(continuar){
        mostrarOpcoesMenuPrincipal();
        printf("\nO que voce deseja fazer?:\t");
        scanf("%d", &opcaoMenuPrincipal);
        entrada[0] = '\0';

        limparTerminal();

        switch (opcaoMenuPrincipal)
        {
        case 1:     //Mostrar interface CPU
            interfaceCPU(registradores, PC, flagZero, registradorInstrucao);
            break;

        case 2:         //Mostrar interface Linhas da Memoria
            interfaceMemoriaLinha(memoria);
            break;

        case 3:          //Mostrar interface Bytes da Memoria
            interfaceMemoriaBytes(memoria);
            break;

        case 4:         //Mostrar intrucoes do Emulador Assembly
            mostrarInstrucoesAssembly();
            break;

        case 5:         //Escrever um codigo Assembly e colocar na memoria
            printf("Digite o codigo em Assembly:\nExemplo: LOADI R4 10\n");
            printf("(por ultimo uma linha em branco)\n\n");
            lerAssemblyTerminal(entrada);                       //ler o codigo assembly passado pelo terminal
            codigoAssembly = separarCodigoAssembly(entrada, &quantPalavras);        //separa o codigo assembly (para processamento)
            traduzParaLinguagemDeMaquina(codigoAssembly, memoria, quantPalavras, &ultimaPosMemoria);                  //traduz o codigo assembly e coloca na memoria
            // printf("\nCodigo carregado na memoria.\n");
            break;

        case 6:           //Executar o codigo Assembly na memoria
            status = executarPrograma(memoria, registradores, &PC, &flagZero, &registradorInstrucao);
            if(status == 0){
                printf("Codigo Assembly foi executado com sucesso\n");
            }else{
                printf("Ocorreu um erro de sintaxe no seu codigo Assembly.\n");
            }
            break;

        case 7:         //Reiniciar estado do Emulador Assembly
            inicializar(registradores, memoria, &PC, &flagZero, &registradorInstrucao);
            printf("Estado do Emulador Assembly reiniciado.");
            break;

        case 8:        //Continuar estado atual do Emulador Assembly
            entrada[0] = '\0';          //esvaziando a entrada
            lerAssemblyTerminal(entrada);
            codigoAssembly = separarCodigoAssembly(entrada, &quantPalavras);
            traduzParaLinguagemDeMaquina(codigoAssembly, memoria, quantPalavras, &ultimaPosMemoria);
            printf("\nCodigo adicional carregado na memoria.\n");
            break;

        case 9:          //Mostrar Opcoes Menu Principal
            limparTerminal();
            getchar();
            printf("Digite o nome do arquivo .asm (ex: codigo.asm): ");
            char nomeArquivo[100];
            scanf("%s", nomeArquivo);

            if (lerAssemblyArquivo(nomeArquivo, entrada) != NULL) {
                codigoAssembly = separarCodigoAssembly(entrada, &quantPalavras);
                traduzParaLinguagemDeMaquina(codigoAssembly, memoria, quantPalavras, &ultimaPosMemoria);
                printf("\nArquivo '%s' carregado e traduzido com sucesso!\n", nomeArquivo);
            } else {
                printf("\nFalha ao carregar o arquivo '%s'. Verifique o nome e tente novamente.\n", nomeArquivo);
            }
            break;


        case 10:         //Encerrar Emulador Assembly
            printf("Voce escolheu encerrar o Emulador Assembly.\n");
            printf("Ate a proxima!");
            sleep(2);                           //aguarda dois segundos antes de fechar o Emulador Assembly
            continuar = FALSE;
            break;

        default:
            limparTerminal();
            printf("[!] Opcao Invalida! Tente novamente.\n");
            break;
        }
        if (continuar) {
            aguardarEnter();
            limparTerminal();
        }
    }
    return 0;
}