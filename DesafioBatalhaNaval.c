#include <stdio.h>

// --- Definições Globais ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define SUCESSO 1 
#define FALHA 0   

// Definições para as Habilidades Especiais
#define TAMANHO_HABILIDADE 5 // Tamanho da matriz de efeito (5x5)
#define AOE_NAO_AFETADA 0    // Posição na matriz de habilidade que não atinge
#define AOE_AFETADA 1        // Posição na matriz de habilidade que atinge
#define MARCA_HABILIDADE 5   // Valor para marcar a área de efeito no tabuleiro principal

// --- Protótipos de Funções ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
// FUNÇÃO DE EXIBIÇÃO CORRIGIDA PARA IMPRIMIR NÚMEROS
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]); 
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);
int verificarLimites(int linha, int coluna, int tamanho, char orientacao);
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao);

// Funções para Habilidades
void criarConeAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarCruzAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criarOctaedroAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicarHabilidadeAoE(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int centro_linha, int centro_coluna);


// --- Função Principal ---
int main() {
    
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    inicializarTabuleiro(tabuleiro);

    // Posicionamento dos Quatro Navios (H, V, P, S)
    posicionarNavio(tabuleiro, 1, 2, TAMANHO_NAVIO, 'H');
    posicionarNavio(tabuleiro, 5, 7, TAMANHO_NAVIO, 'V');
    posicionarNavio(tabuleiro, 0, 0, TAMANHO_NAVIO, 'P');
    posicionarNavio(tabuleiro, 4, 8, TAMANHO_NAVIO, 'S');

    printf("🚢 Navios Posicionados (3).\n");

    // --- Aplicação das Habilidades Especiais (Nível Mestre) ---

    // 1. Criação das Matrizes de Habilidade 5x5
    int aoe_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int aoe_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int aoe_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    
    criarConeAoE(aoe_cone);
    criarCruzAoE(aoe_cruz);
    criarOctaedroAoE(aoe_octaedro);
    
    // 2. Posições de Origem (Centro) no Tabuleiro 10x10
    int centro_cone_r = 7, centro_cone_c = 2;      
    int centro_cruz_r = 5, centro_cruz_c = 5;      
    int centro_octaedro_r = 2, centro_octaedro_c = 7; 
    
    // 3. Aplicação no Tabuleiro Principal
    printf("🔥 Aplicando Habilidades Especiais (5) nas posições:\n");
    printf("   - Cone: (%d, %d)\n", centro_cone_r, centro_cone_c);
    printf("   - Cruz: (%d, %d)\n", centro_cruz_r, centro_cruz_c);
    printf("   - Octaedro: (%d, %d)\n", centro_octaedro_r, centro_octaedro_c);
    
    aplicarHabilidadeAoE(tabuleiro, aoe_cone, centro_cone_r, centro_cone_c);
    aplicarHabilidadeAoE(tabuleiro, aoe_cruz, centro_cruz_r, centro_cruz_c);
    aplicarHabilidadeAoE(tabuleiro, aoe_octaedro, centro_octaedro_r, centro_octaedro_c);
    
    
    // --- 4. Exibição do Tabuleiro Final (Com Números) ---
    printf("\n========================================\n");
    printf(" 🥇 Tabuleiro Final: Nível Mestre 🥇\n");
    printf(" (0=Água | 3=Navio | 5=Habilidade)\n");
    printf("========================================\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}


// ----------------------------------------------------------------------
// Implementação das Funções do Nível Mestre (AoE)
// ----------------------------------------------------------------------


void criarConeAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int dist_h = (j > centro) ? (j - centro) : (centro - j);
            
            if (dist_h <= i) {
                aoe[i][j] = AOE_AFETADA;
            } else {
                aoe[i][j] = AOE_NAO_AFETADA;
            }
        }
    }
}


void criarCruzAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            if (i == centro || j == centro) {
                aoe[i][j] = AOE_AFETADA;
            } else {
                aoe[i][j] = AOE_NAO_AFETADA;
            }
        }
    }
}


void criarOctaedroAoE(int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            int dist_v = (i > centro) ? (i - centro) : (centro - i);
            int dist_h = (j > centro) ? (j - centro) : (centro - j);

            if (dist_v + dist_h <= centro) {
                aoe[i][j] = AOE_AFETADA;
            } else {
                aoe[i][j] = AOE_NAO_AFETADA;
            }
        }
    }
}


void aplicarHabilidadeAoE(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int aoe[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int centro_linha, int centro_coluna) {
    int offset = TAMANHO_HABILIDADE / 2; 
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            if (aoe[i][j] == AOE_AFETADA) {
                
                int r_tab = centro_linha + (i - offset);
                int c_tab = centro_coluna + (j - offset);
                
                // Validação de Limites
                if (r_tab >= 0 && r_tab < TAMANHO_TABULEIRO &&
                    c_tab >= 0 && c_tab < TAMANHO_TABULEIRO) {
                        
                    // Marcação (prioriza o navio, se já estiver lá)
                    if (tabuleiro[r_tab][c_tab] != NAVIO) {
                        tabuleiro[r_tab][c_tab] = MARCA_HABILIDADE; // 5
                    }
                }
            }
        }
    }
}

// ----------------------------------------------------------------------
// Implementação das Funções Auxiliares (Exibição e Posicionamento)
// ----------------------------------------------------------------------


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
             // Imprime o valor numérico da célula (0, 3 ou 5)
             printf("%2d ", tabuleiro[i][j]); 
        }
        printf("|\n");
    }
    printf("  --------------------------------\n");
}


int verificarLimites(int linha, int coluna, int tamanho, char orientacao) {
    int max_coord = TAMANHO_TABULEIRO;

    if (orientacao == 'H') {
        return (linha >= 0 && linha < max_coord && coluna >= 0 && (coluna + tamanho) <= max_coord);
    } else if (orientacao == 'V') {
        return (linha >= 0 && (linha + tamanho) <= max_coord && coluna >= 0 && coluna < max_coord);
    } else if (orientacao == 'P') { // Diagonal Principal
        return (linha >= 0 && (linha + tamanho) <= max_coord && coluna >= 0 && (coluna + tamanho) <= max_coord);
    } else if (orientacao == 'S') { // Diagonal Secundária
        return (linha >= 0 && (linha + tamanho) <= max_coord && coluna >= (tamanho - 1) && coluna < max_coord);
    }
    return FALHA; 
}


int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    for (int i = 0; i < tamanho; i++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            r += i;
        } else if (orientacao == 'P') {
            r += i; 
            c += i;
        } else if (orientacao == 'S') {
            r += i;
            c -= i;
        }

        if (tabuleiro[r][c] == NAVIO) {
            return SUCESSO;
        }
    }
    return FALHA; 
}


int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, char orientacao) {
    
    if (verificarLimites(linha, coluna, tamanho, orientacao) == FALHA) {
        return FALHA;
    }

    if (verificarSobreposicao(tabuleiro, linha, coluna, tamanho, orientacao) == SUCESSO) {
        return FALHA;
    }

    for (int i = 0; i < tamanho; i++) {
        int r = linha;
        int c = coluna;

        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            r += i;
        } else if (orientacao == 'P') {
            r += i;
            c += i; 
        } else if (orientacao == 'S') {
            r += i;
            c -= i;
        }

        tabuleiro[r][c] = NAVIO;
    }

    return SUCESSO;
}