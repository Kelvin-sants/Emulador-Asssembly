//ARQUIVO COM FUNCAO RESPONSAVEL POR LER A MEMORIA DO EMULADOR E EXECUTAR AS INSTRUCOES
// ExecutarAssembly.c
#include <stdio.h>
#include "ExecutarAssembly.h"

#define TRUE 1
#define FALSE 0

// Constantes da arquitetura
#define N_REGISTRADORES 8
#define TAM_MEMORIA 512

// Fetch: busca 4 inteiros da memória na posição PC e armazena em inst
int fetch(int* memoria, int PC, Instrucao* inst) {
    if (PC < 0 || PC + 3 >= TAM_MEMORIA) {
        printf("Erro: PC fora do intervalo da memória no fetch: %d\n", PC);
        return ERRO_ENDERECO_INVALIDO;
    }
    inst->opcode = memoria[PC];
    inst->arg1 = memoria[PC + 1];
    inst->arg2 = memoria[PC + 2];
    inst->arg3 = memoria[PC + 3];
    return 0;
}

// Decode: valida os argumentos da instrução, retorna 0 se ok, erro caso contrário
int decode(Instrucao* inst) {
    int regValido(int r) {
        return (r >= 0 && r < N_REGISTRADORES);
    }
    switch (inst->opcode) {
        case 1: // LOAD
        case 2: // STORE
            if (!regValido(inst->arg1)) {
                printf("Erro: Registrador inválido no decode: R%d\n", inst->arg1 + 1);
                return ERRO_REGISTRADOR_INVALIDO;
            }
            // arg2 é endereço, valida na execução para permitir alteração dinâmica
            break;
        case 3: // ADD
        case 4: // SUB
            if (!regValido(inst->arg1) || !regValido(inst->arg2) || !regValido(inst->arg3)) {
                printf("Erro: Registrador inválido no decode para ADD/SUB\n");
                return ERRO_REGISTRADOR_INVALIDO;
            }
            break;
        case 5: // LOADI
            if (!regValido(inst->arg1)) {
                printf("Erro: Registrador inválido no decode para LOADI: R%d\n", inst->arg1 + 1);
                return ERRO_REGISTRADOR_INVALIDO;
            }
            break;
        case 6: // JUMP
            // arg1 é offset, valida no execute para flexibilidade
            break;
        case 7: // HALT
            // Nenhum argumento a validar
            break;
        default:
            printf("Erro: Opcode inválido no decode: %d\n", inst->opcode);
            return ERRO_INSTRUCAO_INVALIDA;
    }
    return 0;
}

// Execute: executa a instrução e atualiza o estado do programa
int execute(Instrucao* inst, int* memoria, int* registradores, int* PC, int* flagZero) {
    int enderecoValido(int e) {
        return (e >= 0 && e < TAM_MEMORIA);
    }
    switch (inst->opcode) {
        case 1: // LOAD
            if (!enderecoValido(inst->arg2)) {
                printf("Erro: Endereço inválido no LOAD: %d\n", inst->arg2);
                return ERRO_ENDERECO_INVALIDO;
            }
            registradores[inst->arg1] = memoria[inst->arg2];
            break;

        case 2: // STORE
            if (!enderecoValido(inst->arg2)) {
                printf("Erro: Endereço inválido no STORE: %d\n", inst->arg2);
                return ERRO_ENDERECO_INVALIDO;
            }
            memoria[inst->arg2] = registradores[inst->arg1];
            break;

        case 3: // ADD
            registradores[inst->arg1] = registradores[inst->arg2] + registradores[inst->arg3];
            *flagZero = (registradores[inst->arg1] == 0);
            break;

        case 4: // SUB
            registradores[inst->arg1] = registradores[inst->arg2] - registradores[inst->arg3];
            *flagZero = (registradores[inst->arg1] == 0);
            break;

        case 5: // LOADI
            registradores[inst->arg1] = inst->arg2;
            *flagZero = (registradores[inst->arg1] == 0);
            break;

        case 6: // JUMP
        {
            int novoPC = *PC + 4 * inst->arg1;
            if (novoPC < 0 || novoPC >= TAM_MEMORIA) {
                printf("Erro: Endereço inválido no JUMP: %d\n", novoPC);
                return ERRO_ENDERECO_INVALIDO;
            }
            *PC = novoPC;
            return 1; // Indica que o PC já foi atualizado e não deve avançar +4
        }

        case 7: // HALT
            return -999; // Código especial para parar execução

        default:
            printf("Erro: Opcode inválido no execute: %d\n", inst->opcode);
            return ERRO_INSTRUCAO_INVALIDA;
    }
    return 0;
}

// Função principal que executa o programa em loop usando fetch, decode e execute
int executarPrograma(int* memoria, int* registradores, int* PC, int* flagZero, int* registradorInstrucao) {
    int continuar = TRUE;
    Instrucao inst;

    while (continuar) {
        int fetchStatus = fetch(memoria, *PC, &inst);
        if (fetchStatus != 0) return fetchStatus;

        *registradorInstrucao = inst.opcode;

        int decodeStatus = decode(&inst);
        if (decodeStatus != 0) return decodeStatus;

        int executeStatus = execute(&inst, memoria, registradores, PC, flagZero);

        if (executeStatus == -999) { // HALT
            continuar = FALSE;
        } else if (executeStatus == 1) {
            // PC já foi atualizado no JUMP, não incrementar
        } else if (executeStatus != 0) {
            return executeStatus; // algum erro na execução
        } else {
            *PC += 4; // avanço padrão para próxima instrução
        }
    }

    return 0; // sucesso
}

