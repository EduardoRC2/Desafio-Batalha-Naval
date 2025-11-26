#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.


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
// Funções de validação e posicionamento atualizadas para incluir diagonais ('P' e 'S')
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);
int verificarLimites(int linha, int coluna, int tamanho, char orientacao);
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);


int main() {
    
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    
    inicializarTabuleiro(tabuleiro);

    // --- Coordenadas dos Quatro Navios (Incluindo os Diagonais) ---

    // Navio 1: Horizontal (H)
    int navio1_linha = 1;
    int navio1_coluna = 2;
    char navio1_orientacao = 'H'; 

    // Navio 2: Vertical (V)
    int navio2_linha = 5;
    int navio2_coluna = 7;
    char navio2_orientacao = 'V'; 
    
    // Navio 3: Diagonal Principal (P) - Linha e Coluna aumentam (Ex: (0,0) -> (1,1) -> (2,2))
    int navio3_linha = 0; 
    int navio3_coluna = 0; 
    char navio3_orientacao = 'P'; 

    // Navio 4: Diagonal Secundária (S) - Linha aumenta, Coluna diminui (Ex: (4,8) -> (5,7) -> (6,6))
    int navio4_linha = 4;
    int navio4_coluna = 8;
    char navio4_orientacao = 'S'; 

    
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

    printf("\n🚢 Tentando posicionar Navio 3 (Diagonal P) em (%d, %d)...\n", navio3_linha, navio3_coluna);
    if (posicionarNavio(tabuleiro, navio3_linha, navio3_coluna, TAMANHO_NAVIO, navio3_orientacao) == SUCESSO) {
        printf("✅ Navio 3 posicionado com sucesso!\n");
    } else {
        printf("❌ Falha ao posicionar Navio 3. Verifique limites ou sobreposição.\n");
    }

    printf("\n🚢 Tentando posicionar Navio 4 (Diagonal S) em (%d, %d)...\n", navio4_linha, navio4_coluna);
    if (posicionarNavio(tabuleiro, navio4_linha, navio4_coluna, TAMANHO_NAVIO, navio4_orientacao) == SUCESSO) {
        printf("✅ Navio 4 posicionado com sucesso!\n");
    } else {
        printf("❌ Falha ao posicionar Navio 4. Verifique limites ou sobreposição.\n");
    }
    
    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.
    
    printf("\n========================================\n");
    printf(" 🌊 Tabuleiro Aventureiro (4 Navios) 🌊\n");
    printf("   (H, V, Diagonal P, Diagonal S)\n");
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
    int max_coord = TAMANHO_TABULEIRO;

    if (orientacao == 'H') {
        // Navio Horizontal: A coluna final deve estar dentro do limite [0, 9].
        return (linha >= 0 && linha < max_coord && 
                coluna >= 0 && (coluna + tamanho) <= max_coord);
    } else if (orientacao == 'V') {
        // Navio Vertical: A linha final deve estar dentro do limite [0, 9].
        return (linha >= 0 && (linha + tamanho) <= max_coord && 
                coluna >= 0 && coluna < max_coord);
    } else if (orientacao == 'P') {
        // Diagonal Principal (r e c aumentam): As coordenadas finais devem ser <= 10.
        return (linha >= 0 && (linha + tamanho) <= max_coord &&
                coluna >= 0 && (coluna + tamanho) <= max_coord);
    } else if (orientacao == 'S') {
        // Diagonal Secundária (r aumenta, c diminui): Linha final <= 10 e Coluna final (coluna - tamanho + 1) >= 0.
        return (linha >= 0 && (linha + tamanho) <= max_coord &&
                coluna >= (tamanho - 1) && coluna < max_coord); // Garante que a coluna não fique negativa
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
        } else if (orientacao == 'P') {
            r += i; // Linha aumenta
            c += i; // Coluna aumenta
        } else if (orientacao == 'S') {
            r += i; // Linha aumenta
            c -= i; // Coluna diminui
        }

        // Verifica se a posição já está ocupada por um navio (valor 3)
        if (tabuleiro[r][c] == NAVIO) {
            return SUCESSO; // Sobreposição encontrada
        }
    }
    return FALHA; 
}



int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    
    // 1. Validação de Limites
    if (verificarLimites(linha, coluna, tamanho, orientacao) == FALHA) {
        printf("   (ERRO: Navio fora dos limites do tabuleiro.)\n");
        return FALHA;
    }

    // 2. Validação de Sobreposição
    if (verificarSobreposicao(tabuleiro, linha, coluna, tamanho, orientacao) == SUCESSO) {
        printf("   (ERRO: Navio se sobrepõe a outro navio já existente.)\n");
        return FALHA;
    }

    // 3. Posicionamento (Marca as células com 3)
    for (int i = 0; i < tamanho; i++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += i; // Navio horizontal: a coluna avança
        } else if (orientacao == 'V') {
            r += i; // Navio vertical: a linha avança
        } else if (orientacao == 'P') {
            r += i; // Diagonal Principal: Linha e Coluna avançam
            c += i; 
        } else if (orientacao == 'S') {
            r += i; // Diagonal Secundária: Linha avança
            c -= i; // Coluna retrocede
        }

        // Marca a posição no tabuleiro com o valor 3
        tabuleiro[r][c] = NAVIO;
    }

    return SUCESSO; // Navio posicionado com sucesso
}


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