#ifndef INTERFACE_H
#define INTERFACE_H

void interfaceCPU(int* registradores, int PC, int flagZero, int registradorInstrucao);
void interfaceMemoriaBytes(int* memoria);
void interfaceMemoriaLinha(int* memoria);
void limparTerminal();
void mostrarInstrucoesAssembly();
void mostrarOpcoesMenuPrincipal();

#endif
