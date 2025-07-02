#ifndef LER_ASSEMBLY_H
#define LER_ASSEMBLY_H

char* lerAssemblyTerminal(char* entrada);
char** separarCodigoAssembly(char* entrada, int *qtdPalavras);
int devolveRegistrador(char* registrador);
void traduzParaLinguagemDeMaquina(char** codigoAssembly, int* memoria, int quantPalavras, int *ultimaPosMemoria);
char* lerAssemblyArquivo(const char* nomeArquivo, char* entrada);

#endif
