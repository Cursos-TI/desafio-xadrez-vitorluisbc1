#include <stdio.h>
#include <stdbool.h>

// Constantes para o tamanho do tabuleiro
#define TAMANHO 8

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n  a b c d e f g h\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 1) {
                printf("X ");
            } else if (tabuleiro[i][j] == 2) {
                printf("O ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para limpar o tabuleiro
void limparTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Movimentação do Bispo (recursiva)
void moverBispo(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, int direcao) {
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
        return;
    }
    
    tabuleiro[linha][coluna] = 1;
    
    // 4 direções diagonais
    switch (direcao) {
        case 1: moverBispo(tabuleiro, linha-1, coluna-1, direcao); break; // Superior esquerdo
        case 2: moverBispo(tabuleiro, linha-1, coluna+1, direcao); break; // Superior direito
        case 3: moverBispo(tabuleiro, linha+1, coluna-1, direcao); break; // Inferior esquerdo
        case 4: moverBispo(tabuleiro, linha+1, coluna+1, direcao); break; // Inferior direito
    }
}

// Movimentação da Torre (usando loops)
void moverTorre(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    // Movimento para cima
    for (int i = linha - 1; i >= 0; i--) {
        tabuleiro[i][coluna] = 1;
    }
    
    // Movimento para baixo
    for (int i = linha + 1; i < TAMANHO; i++) {
        tabuleiro[i][coluna] = 1;
    }
    
    // Movimento para esquerda
    for (int j = coluna - 1; j >= 0; j--) {
        tabuleiro[linha][j] = 1;
    }
    
    // Movimento para direita
    for (int j = coluna + 1; j < TAMANHO; j++) {
        tabuleiro[linha][j] = 1;
    }
}

// Movimentação da Rainha (combina torre e bispo)
void moverRainha(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    // Movimentos como torre
    moverTorre(tabuleiro, linha, coluna);
    
    // Movimentos como bispo (todas as direções)
    for (int dir = 1; dir <= 4; dir++) {
        moverBispo(tabuleiro, linha, coluna, dir);
    }
}

// Movimentação do Cavalo (em L)
void moverCavalo(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna) {
    // Todas as possíveis movimentações em L
    int movimentos[8][2] = {
        {linha-2, coluna-1}, {linha-2, coluna+1},
        {linha-1, coluna-2}, {linha-1, coluna+2},
        {linha+1, coluna-2}, {linha+1, coluna+2},
        {linha+2, coluna-1}, {linha+2, coluna+1}
    };
    
    for (int i = 0; i < 8; i++) {
        int novaLinha = movimentos[i][0];
        int novaColuna = movimentos[i][1];
        
        if (novaLinha >= 0 && novaLinha < TAMANHO && novaColuna >= 0 && novaColuna < TAMANHO) {
            tabuleiro[novaLinha][novaColuna] = 2; // Usando 2 para diferenciar do bispo
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int linha, coluna;
    char colunaChar;
    
    printf("=== SIMULADOR DE MOVIMENTAÇÃO DE PEÇAS DE XADREZ ===\n");
    
    // Posição inicial da peça
    printf("\nDigite a posição inicial (ex: e4): ");
    scanf(" %c%d", &colunaChar, &linha);
    
    // Converter entrada para índices da matriz
    coluna = colunaChar - 'a';
    linha = 8 - linha;
    
    // Verificar se a posição é válida
    if (linha < 0 || linha >= TAMANHO || coluna < 0 || coluna >= TAMANHO) {
        printf("Posição inválida!\n");
        return 1;
    }
    
    // Menu de seleção de peça
    printf("\nSelecione a peça:\n");
    printf("1. Bispo\n");
    printf("2. Torre\n");
    printf("3. Rainha\n");
    printf("4. Cavalo\n");
    printf("Escolha: ");
    
    int opcao;
    scanf("%d", &opcao);
    
    limparTabuleiro(tabuleiro);
    tabuleiro[linha][coluna] = 9; // Marcando a posição inicial
    
    switch (opcao) {
        case 1: // Bispo
            for (int dir = 1; dir <= 4; dir++) {
                moverBispo(tabuleiro, linha, coluna, dir);
            }
            printf("\nMovimentos possíveis do Bispo:\n");
            break;
            
        case 2: // Torre
            moverTorre(tabuleiro, linha, coluna);
            printf("\nMovimentos possíveis da Torre:\n");
            break;
            
        case 3: // Rainha
            moverRainha(tabuleiro, linha, coluna);
            printf("\nMovimentos possíveis da Rainha:\n");
            break;
            
        case 4: // Cavalo
            moverCavalo(tabuleiro, linha, coluna);
            printf("\nMovimentos possíveis do Cavalo:\n");
            break;
            
        default:
            printf("Opção inválida!\n");
            return 1;
    }
    
    imprimirTabuleiro(tabuleiro);
    
    printf("Legenda:\n");
    printf("9 - Posição inicial da peça\n");
    printf("X - Movimentos possíveis (Bispo/Torre/Rainha)\n");
    printf("O - Movimentos possíveis (Cavalo)\n");
    printf(". - Casas não alcançáveis\n");
    
    return 0;
}