//ARQUIVO COM FUNCAO RESPONSAVEL POR LER A MEMORIA DO EMULADOR E EXECUTAR AS INSTRUCOES
#define TRUE 1
#define FALSE 0


int executarPrograma(int* memoria, int* registradores, int* PC, int* flagZero, int* registradorInstrucao) {

    int continuar = TRUE;

    // Inicia Loop
    while (continuar) {

        // Fase de busca e decodificação 
        int opcode = memoria[*PC];
        int arg1 = memoria[*PC + 1];
        int arg2 = memoria[*PC + 2];
        int arg3 = memoria[*PC + 3];

        *registradorInstrucao = opcode;                 // Salva a instrução atual

        switch (opcode) {
            case 1:  // LOAD    
                registradores[arg1] = memoria[arg2 - 1];                //memoria[arg2 - 1] porque quando o usuario pede a posicao n da memoria essa posicao esta fisicamente em n - 1
                break;

            case 2:  // STORE
                memoria[arg2 - 1] = registradores[arg1];
                break;

            case 3:  // ADD
                registradores[arg1] = registradores[arg2] + registradores[arg3];
                *flagZero = (registradores[arg1] == 0);
                break;

            case 4:  // SUB 
                registradores[arg1] = registradores[arg2] - registradores[arg3];
                *flagZero = (registradores[arg1] == 0);                 // Atualiza flag
                break;

            case 5:  // LOADI
                registradores[arg1] = arg2;
                *flagZero = (registradores[arg1] == 0);                 // Atualiza flag
                break;

            case 6:  // JUMP
                *PC += 4 * arg1;
                continue;                                               // pula o incremento padrão
                break;

            case 7:  // HALT
                continuar = FALSE;
                break;  //Finalizada com sucesso

            default:                        //se pegar um 0
                return -1; // Erro 
                break;
        }

        *PC += 4;               //PC aponta para proxima instrucao depois das intrucoes executadas
    }
    return 0;
}
