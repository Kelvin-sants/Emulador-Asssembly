#include <stdio.h>
#include <string.h>

int main() {
    char linha[100];
    char instrucao[10], operando1[10], operando2[10];
    
    printf("=== Leitura de Código Assembly ===\n");
    printf("Digite suas instruções (uma por linha).\n");
    printf("Termine com Ctrl+D (Linux/Mac) ou Ctrl+Z (Windows):\n\n");
    
    int contador = 0;
    
    // Lê todas as linhas até o fim da entrada
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        // Remove o '\n' do final da linha
        linha[strcspn(linha, "\n")] = 0;
        
        // Pula linhas vazias
        if (strlen(linha) == 0) {
            continue;
        }
        
        // Separa a linha em 3 partes
        int tokens = sscanf(linha, "%s %s %s", instrucao, operando1, operando2);
        
        if (tokens == 3) {
            printf("Linha %d: '%s' '%s' '%s'\n", contador, instrucao, operando1, operando2);
            contador++;
        } else {
            printf("Linha %d: ERRO - Formato inválido: '%s'\n", contador, linha);
        }
    }
    
    printf("\nTotal de linhas processadas: %d\n", contador);
    return 0;
}