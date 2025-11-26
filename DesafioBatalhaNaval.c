#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.


    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    

// Definições para o tabuleiro e navios (Requisitos fixos)
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define SUCESSO 1 // Representa VERDADEIRO (true)
#define FALHA 0   // Representa FALSO (false)

// --- Protótipos de Funções ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);
int verificarLimites(int linha, int coluna, int tamanho, char orientacao);
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);



int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    
    inicializarTabuleiro(tabuleiro);

    
    int navio1_linha = 1;
    int navio1_coluna = 2;
    char navio1_orientacao = 'H'; 

    
    int navio2_linha = 5;
    int navio2_coluna = 7;
    char navio2_orientacao = 'V'; 

    
    printf("🚢 Tentando posicionar Navio 1 (Horizontal) em (%d, %d)...\n", navio1_linha, navio1_coluna);
    if (posicionarNavio(tabuleiro, navio1_linha, navio1_coluna, TAMANHO_NAVIO, navio1_orientacao) == SUCESSO) {
        printf("✅ Navio 1 posicionado com sucesso!\n");
    } else {
        printf("❌ Falha ao posicionar Navio 1. Verifique limites ou sobreposição.\n");
    }

    printf("\n🚢 Tentando posicionar Navio 2 (Vertical) em (%d, %d)...\n", navio2_linha, navio2_coluna);
    if (posicionarNavio(tabuleiro, navio2_linha, navio2_coluna, TAMANHO_NAVIO, navio2_orientacao) == SUCESSO) {
        printf("✅ Navio 2 posicionado com sucesso!\n");
    } else {
        printf("❌ Falha ao posicionar Navio 2. Verifique limites ou sobreposição.\n");
    }
    
    
    printf("\n========================================\n");
    printf("       🌊 Tabuleiro de Batalha Naval 🌊\n");
    printf("   (0 = Água | 3 = Navio)\n");
    printf("========================================\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}


void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA; 
        }
    }
}


void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    
    printf("   "); 
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j); 
    }
    printf("\n");
    printf("  --------------------------------\n");

    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i); 
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]); 
        }
        printf("|\n");
    }
    printf("  --------------------------------\n");
}



int verificarLimites(int linha, int coluna, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        // Navio Horizontal: A coluna final deve estar dentro do limite (TAMANHO_TABULEIRO - 1).
        if (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && (coluna + tamanho) <= TAMANHO_TABULEIRO) {
            return SUCESSO;
        }
    } else if (orientacao == 'V') {
        // Navio Vertical: A linha final deve estar dentro do limite (TAMANHO_TABULEIRO - 1).
        if (linha >= 0 && (linha + tamanho) <= TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO) {
            return SUCESSO;
        }
    }
    return FALHA; 
}


int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    // Percorre as 'tamanho' posições que o novo navio ocuparia
    for (int i = 0; i < tamanho; i++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += i; // A coluna muda para o navio horizontal
        } else if (orientacao == 'V') {
            r += i; // A linha muda para o navio vertical
        }

        // Verifica se a posição já está ocupada por um navio (valor 3)
        if (tabuleiro[r][c] == NAVIO) {
            return SUCESSO; // Sobreposição encontrada
        }
    }
    return FALHA; 
}



int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    
    if (verificarLimites(linha, coluna, tamanho, orientacao) == FALHA) {
        printf("   (ERRO: Navio fora dos limites do tabuleiro.)\n");
        return FALHA;
    }

    
    if (verificarSobreposicao(tabuleiro, linha, coluna, tamanho, orientacao) == SUCESSO) {
        printf("   (ERRO: Navio se sobrepõe a outro navio já existente.)\n");
        return FALHA;
    }

    
    for (int i = 0; i < tamanho; i++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += i; // Navio horizontal: a coluna avança
        } else if (orientacao == 'V') {
            r += i; // Navio vertical: a linha avança
        }

        // Marca a posição no tabuleiro com o valor 3
        tabuleiro[r][c] = NAVIO;
    }

    return SUCESSO; // Navio posicionado com sucesso
}

    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    