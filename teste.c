#include <stdio.h>
#include <string.h>

int main() {
    char linha[100];
    char instrucao[10], operando1[10], operando2[10];
    
    printf("=== Leitura de Código Assembly ===\n");
    printf("Digite uma instrução (ex: ADD 10 R4):\n");
    
    while (1) {
        printf("Assembly> ");
        
        // Lê a linha completa do terminal
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }
        
        // Remove o '\n' do final da linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Verifica se quer sair
        if (strcmp(linha, "sair") == 0) {
            break;
        }
        
        // Separa a linha em 3 partes: instrução, operando1, operando2
        int tokens = sscanf(linha, "%s %s %s", instrucao, operando1, operando2);
        
        // Verifica se conseguiu ler 3 tokens
        if (tokens == 3) {
            printf("Instrução lida: '%s'\n", instrucao);
            printf("Operando 1: '%s'\n", operando1);
            printf("Operando 2: '%s'\n", operando2);
            printf("---\n");
        } else {
            printf("Erro: Formato inválido. Use: INSTRUCAO OPERANDO1 OPERANDO2\n");
        }
    }
    
    printf("Programa encerrado.\n");
    return 0;
}