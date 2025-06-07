#include <stdio.h>

// Define constantes para facilitar a manutenção do código.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Protótipo da função para exibir o tabuleiro.
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int pode_posicionar; // Flag para controlar se o posicionamento é válido.

    // Inicializa todo o tabuleiro com o valor 0 (água).
    printf("Inicializando o tabuleiro %dx%d com água (0)...\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // --- Posicionamento dos Navios ---

    // 1. Navio Horizontal
    int navio_h_linha = 9;
    int navio_h_coluna = 1;
    pode_posicionar = 1;
    if (navio_h_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio horizontal fora dos limites!\n");
        pode_posicionar = 0;
    }
    if(pode_posicionar) {
        printf("Posicionando navio horizontal em (%d, %d).\n", navio_h_linha, navio_h_coluna);
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = 3;
        }
    }

    // 2. Navio Vertical
    int navio_v_linha = 4;
    int navio_v_coluna = 8;
    pode_posicionar = 1;
    if (navio_v_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio vertical fora dos limites!\n");
        pode_posicionar = 0;
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_v_linha + i][navio_v_coluna] != 0) {
                printf("Erro: Sobreposição no navio vertical!\n");
                pode_posicionar = 0;
                break;
            }
        }
    }
    if (pode_posicionar) {
        printf("Posicionando navio vertical em (%d, %d).\n", navio_v_linha, navio_v_coluna);
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_v_linha + i][navio_v_coluna] = 3;
        }
    }

    // 3. Navio Diagonal (Principal: linha e coluna aumentam)
    int navio_d1_linha = 0;
    int navio_d1_coluna = 0;
    pode_posicionar = 1;
    if (navio_d1_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || navio_d1_coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: Navio diagonal 1 fora dos limites!\n");
        pode_posicionar = 0;
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_d1_linha + i][navio_d1_coluna + i] != 0) {
                printf("Erro: Sobreposição no navio diagonal 1!\n");
                pode_posicionar = 0;
                break;
            }
        }
    }
    if (pode_posicionar) {
        printf("Posicionando navio diagonal 1 em (%d, %d).\n", navio_d1_linha, navio_d1_coluna);
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_d1_linha + i][navio_d1_coluna + i] = 3;
        }
    }

    // 4. Navio Diagonal (Secundária: linha aumenta, coluna diminui)
    int navio_d2_linha = 1;
    int navio_d2_coluna = 4;
    pode_posicionar = 1;
    if (navio_d2_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || navio_d2_coluna - (TAMANHO_NAVIO - 1) < 0) {
        printf("Erro: Navio diagonal 2 fora dos limites!\n");
        pode_posicionar = 0;
    } else {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_d2_linha + i][navio_d2_coluna - i] != 0) {
                printf("Erro: Sobreposição no navio diagonal 2!\n");
                pode_posicionar = 0;
                break;
            }
        }
    }
    if (pode_posicionar) {
        printf("Posicionando navio diagonal 2 em (%d, %d).\n", navio_d2_linha, navio_d2_coluna);
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_d2_linha + i][navio_d2_coluna - i] = 3;
        }
    }

    // Exibe o tabuleiro final.
    printf("\n--- Tabuleiro Final de Batalha Naval ---\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 * @param tabuleiro A matriz 10x10 que representa o tabuleiro.
 * Esta função percorre a matriz e imprime cada célula de forma organizada.
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Adiciona cabeçalho para as colunas.
    printf("  "); 
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        printf("%d ", i);
    }
    printf("\n");

    // Percorre as linhas e colunas para imprimir o tabuleiro.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Imprime o número da linha.
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula.
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n"); // Pula para a próxima linha no console.
    }
}
