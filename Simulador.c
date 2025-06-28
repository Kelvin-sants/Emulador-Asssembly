#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "LerAssembly.c"
#include "ExecutarAssembly.c"
#include "Interface.c"
#define TAM_MEMORIA 512
#define N_registradores 8
#define TAM_ENTRADA  300
#define TRUE 1
#define FALSE 0

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
    
    inicializar(registradores, memoria, &PC, &flagZero, &registradorInstrucao);               //inicializa tudo como 0;

    limparTerminal();
    printf("Bem vindo ao emulador de Assembly\n\n");
    mostrarOpcoesMenuPrincipal();
    printf("\n");

    while(continuar){
        
        printf("\nO que voce deseja fazer:\t");
        scanf("%d", &opcaoMenuPrincipal);

        switch (opcaoMenuPrincipal)
        {
        case 1:     //Mostrar interface CPU
            limparTerminal();
            interfaceCPU(registradores, PC, flagZero, registradorInstrucao);
            break;

        case 2:         //Mostrar interface Linhas da Memoria
            limparTerminal();
            interfaceMemoriaLinha(memoria);
            break;

        case 3:          //Mostrar interface Bytes da Memoria
            limparTerminal();
            interfaceMemoriaBytes(memoria);
            break;

        case 4:         //Mostrar intrucoes do Emulador Assembly
            limparTerminal();
            mostrarInstrucoesAssembly();
            break;

        case 5:         //Escrever um codigo Assembly e colocar na memoria

            limparTerminal();
            printf("Digite o codigo em Assembly:\nExemplo: LOADI R4 10\n");
            printf("(por ultimo uma linha em branco)\n\n");
            lerAssemblyTerminal(entrada);                       //ler o codigo assembly passado pelo terminal
            codigoAssembly = separarCodigoAssembly(entrada, &quantPalavras);        //separa o codigo assembly (para processamento)
            traduzParaLinguagemDeMaquina(codigoAssembly, memoria, quantPalavras, &ultimaPosMemoria);                  //traduz o codigo assembly e coloca na memoria
            break;

        case 6:           //Executar o codigo Assembly na memoria
            
            limparTerminal();
            int status = executarPrograma(memoria, registradores, &PC, &flagZero, &registradorInstrucao);
            if(status == 0){
                printf("Seu codigo assembly foi executado com sucesso\n");
            }else{
                printf("Houve um erro de sintaxe no seu codigo assembly\n");
            }
            break;

        case 7:         //Reiniciar estado do Emulador Assembly
            
            limparTerminal();
            inicializar(registradores, memoria, &PC, &flagZero, &registradorInstrucao);
            printf("O estador do Emulador Assembly foi reiniciado");
            break;

        case 8:        //Continuar estado atual do Emulador Assembly
            
            entrada[0] = '\0';          //esvaziando a entrada
            lerAssemblyTerminal(entrada);
            codigoAssembly = separarCodigoAssembly(entrada, &quantPalavras);
            traduzParaLinguagemDeMaquina(codigoAssembly, memoria, quantPalavras, &ultimaPosMemoria);
            break;

        case 9:          //Mostrar Opcoes Menu Principal
            limparTerminal();
            mostrarOpcoesMenuPrincipal();
            break;

        case 10:         //Encerrar Emulador Assembly
            limparTerminal();
            printf("Voce escolheu encerrar o Emulador Assembly\n");
            printf("Ate a proxima");
            sleep(2);                           //aguarda dois segundos antes de fechar o Emulador Assembly
            continuar = FALSE;
            break;

        default:
            limparTerminal();
            printf("Opcao Invalida\n");
            break;
        }
    }
}