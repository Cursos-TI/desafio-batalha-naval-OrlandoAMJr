#include <stdio.h>

// Define constantes para facilitar a manutenção do código.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Protótipo da função para exibir o tabuleiro.
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todo o tabuleiro com o valor 0 (água).
    printf("Inicializando o tabuleiro %dx%d com água (0)...\n", TAMANHO_TABULEIRO, TAMANHO_TABULEIRO);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // --- Posicionamento dos Navios ---

    // Coordenadas iniciais do navio horizontal.
    int navio_h_linha = 2;
    int navio_h_coluna = 1;

    // Verifica se o navio horizontal cabe nos limites do tabuleiro.
    if (navio_h_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        printf("Posicionando navio horizontal de tamanho %d na linha %d, coluna %d.\n", TAMANHO_NAVIO, navio_h_linha, navio_h_coluna);
        // Posiciona o navio horizontal (valor 3).
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = 3;
        }
    } else {
        printf("Erro: O navio horizontal está fora dos limites do tabuleiro!\n");
    }

    // Coordenadas iniciais do navio vertical.
    int navio_v_linha = 4;
    int navio_v_coluna = 5;

    // Flag para controlar se o posicionamento é válido (1 = true, 0 = false).
    int pode_posicionar = 1; 

    // Valida se o navio vertical cabe no tabuleiro.
    if (navio_v_linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
        printf("Erro: O navio vertical está fora dos limites do tabuleiro!\n");
        pode_posicionar = 0;
    } else {
        // Valida se há sobreposição com outro navio.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio_v_linha + i][navio_v_coluna] != 0) {
                printf("Erro: Sobreposição detectada! O navio vertical não pode ser posicionado.\n");
                pode_posicionar = 0;
                break; // Interrompe a verificação se encontrar sobreposição.
            }
        }
    }
    
    // Se, após as validações, for possível, posiciona o navio.
    if (pode_posicionar) {
        printf("Posicionando navio vertical de tamanho %d na linha %d, coluna %d.\n", TAMANHO_NAVIO, navio_v_linha, navio_v_coluna);
        // Posiciona o navio vertical (valor 3).
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_v_linha + i][navio_v_coluna] = 3;
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
