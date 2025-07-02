#ifndef EXECUTAR_ASSEMBLY_H
#define EXECUTAR_ASSEMBLY_H

// Constantes de erro
#define ERRO_INSTRUCAO_INVALIDA -1
#define ERRO_REGISTRADOR_INVALIDO -2
#define ERRO_ENDERECO_INVALIDO -3

// Estrutura para representar uma instrução
typedef struct {
    int opcode;
    int arg1;
    int arg2;
    int arg3;
} Instrucao;

// Protótipos das funções do ciclo fetch-decode-execute
int fetch(int* memoria, int PC, Instrucao* inst);
int decode(Instrucao* inst);
int execute(Instrucao* inst, int* memoria, int* registradores, int* PC, int* flagZero);
int executarPrograma(int* memoria, int* registradores, int* PC, int* flagZero, int* registradorInstrucao);

#endif

