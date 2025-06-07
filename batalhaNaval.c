#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

// --- Constantes Globais ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define HABILIDADE_TAMANHO 5 // Tamanho das matrizes de habilidade (ex: 5x5)

// --- Valores do Tabuleiro ---
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// --- Protótipos das Funções ---
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

// Funções para criar e aplicar habilidades
void criarMatrizCone(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho);
void criarMatrizCruz(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho);
void criarMatrizOctaedro(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho);
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int origem_linha, int origem_coluna);


int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Matrizes para cada habilidade especial
    int habilidade_cone[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int habilidade_cruz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];
    int habilidade_octaedro[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO];

    // 1. Prepara o tabuleiro e os navios
    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);
    
    printf("\n--- Tabuleiro com Navios Posicionados ---\n");
    exibirTabuleiro(tabuleiro);

    // 2. Cria as matrizes de habilidade dinamicamente
    printf("\nCriando matrizes de habilidade de tamanho %dx%d...\n", HABILIDADE_TAMANHO, HABILIDADE_TAMANHO);
    criarMatrizCone(habilidade_cone, HABILIDADE_TAMANHO);
    criarMatrizCruz(habilidade_cruz, HABILIDADE_TAMANHO);
    criarMatrizOctaedro(habilidade_octaedro, HABILIDADE_TAMANHO);

    // 3. Aplica as habilidades no tabuleiro em posições definidas
    printf("Aplicando habilidades no tabuleiro...\n");
    aplicarHabilidade(tabuleiro, habilidade_cone, 2, 6);      // Origem do cone em (2, 6)
    aplicarHabilidade(tabuleiro, habilidade_cruz, 6, 3);      // Origem da cruz em (6, 3)
    aplicarHabilidade(tabuleiro, habilidade_octaedro, 3, 1);  // Origem do octaedro em (3, 1)

    // 4. Exibe o tabuleiro final com as áreas de efeito
    printf("\n--- Tabuleiro Final com Habilidades ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Inicializa o tabuleiro com o valor de ÁGUA.
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Posiciona 4 navios (horizontal, vertical, 2 diagonais) no tabuleiro.
 */
void posicionarNavios(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Navio Horizontal
    tabuleiro[9][1] = NAVIO; tabuleiro[9][2] = NAVIO; tabuleiro[9][3] = NAVIO;
    // Navio Vertical
    tabuleiro[0][8] = NAVIO; tabuleiro[1][8] = NAVIO; tabuleiro[2][8] = NAVIO;
    // Navio Diagonal 1
    tabuleiro[0][0] = NAVIO; tabuleiro[1][1] = NAVIO; tabuleiro[2][2] = NAVIO;
    // Navio Diagonal 2
    tabuleiro[5][5] = NAVIO; tabuleiro[6][4] = NAVIO; tabuleiro[7][3] = NAVIO;
}


/**
 * @brief Gera uma matriz de habilidade em forma de cone.
 * A lógica expande a área afetada a cada linha.
 */
void criarMatrizCone(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // A condição verifica se a coluna 'j' está dentro do alcance do cone para a linha 'i'.
            if (j >= centro - i && j <= centro + i) {
                matriz[i][j] = 1; // Área afetada
            } else {
                matriz[i][j] = 0; // Área não afetada
            }
        }
    }
}

/**
 * @brief Gera uma matriz de habilidade em forma de cruz.
 * A lógica ativa a linha e a coluna centrais.
 */
void criarMatrizCruz(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // A condição verifica se a célula está na linha central OU na coluna central.
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Gera uma matriz de habilidade em forma de octaedro (losango).
 * Utiliza a "distância de Manhattan" do centro.
 */
void criarMatrizOctaedro(int matriz[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int tamanho) {
    int centro = tamanho / 2;
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            // A soma das distâncias absolutas do centro define a forma de losango.
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de uma habilidade no tabuleiro principal.
 * @param origem_linha A linha do tabuleiro onde o centro da habilidade será aplicado.
 * @param origem_coluna A coluna do tabuleiro onde o centro da habilidade será aplicado.
 */
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[HABILIDADE_TAMANHO][HABILIDADE_TAMANHO], int origem_linha, int origem_coluna) {
    int centro_habilidade = HABILIDADE_TAMANHO / 2;

    // Itera pela matriz da habilidade
    for (int i = 0; i < HABILIDADE_TAMANHO; i++) {
        for (int j = 0; j < HABILIDADE_TAMANHO; j++) {
            // Verifica se esta parte da habilidade afeta uma área (valor 1)
            if (habilidade[i][j] == 1) {
                // Calcula a posição correspondente no tabuleiro principal
                int linha_tabuleiro = origem_linha - centro_habilidade + i;
                int coluna_tabuleiro = origem_coluna - centro_habilidade + j;

                // Garante que a posição está dentro dos limites do tabuleiro
                if (linha_tabuleiro >= 0 && linha_tabuleiro < TAMANHO_TABULEIRO &&
                    coluna_tabuleiro >= 0 && coluna_tabuleiro < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro como afetada pela habilidade
                    tabuleiro[linha_tabuleiro][coluna_tabuleiro] = HABILIDADE;
                }
            }
        }
    }
}


/**
 * @brief Exibe o tabuleiro no console com caracteres especiais.
 * ~: Água, N: Navio, *: Área de Habilidade
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Cabeçalho das colunas
    printf("   "); 
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        printf("%d ", i);
    }
    printf("\n");
    printf("   --------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d |", i); // Número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo;
            switch (tabuleiro[i][j]) {
                case AGUA:       simbolo = '~'; break;
                case NAVIO:      simbolo = 'N'; break;
                case HABILIDADE: simbolo = '*'; break;
                default:         simbolo = '?'; break;
            }
            printf(" %c", simbolo);
        }
        printf("\n");
    }
}
