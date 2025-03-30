#include "antenas.h"

/**
 * @brief Função principal do programa.
 * 
 * Esta função exibe um menu de opções para o usuário, permitindo a interação com o sistema de antenas.
 * O programa permite carregar antenas de um arquivo, inserir novas antenas, remover antenas, listar antenas,
 * deduzir localizações com efeito nefasto, e mostrar o mapa de antenas.
 * O loop continua até que o usuário escolha a opção de sair.
 * 
 * @return Retorna 0 se o programa for executado com sucesso.
 */
int main() {
    Antena* lista = NULL; ///< Ponteiro para a lista de antenas, inicialmente vazio.
    int opcao; ///< Variável para armazenar a opção escolhida pelo usuário.
    char nomeArquivo[50]; ///< Nome do arquivo que será utilizado para carregar antenas.

    do {
        // Exibe o menu de opções.
        printf("\n===== Menu =====\n");
        printf("1. Carregar Antenas de Arquivo\n");
        printf("2. Inserir Nova Antena\n");
        printf("3. Remover Antena\n");
        printf("4. Listar Antenas\n");
        printf("5. Deduzir Localizações com Efeito Nefasto\n");
        printf("6. Mostrar Mapa\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Carregar antenas a partir de um arquivo.
                printf("Digite o nome do arquivo: ");
                scanf("%s", nomeArquivo);
                carregarAntenasDoArquivo(&lista, nomeArquivo);
                break;
            }
            case 2: {
                // Inserir uma nova antena.
                char freq; ///< Frequência da antena.
                int x, y; ///< Posições da antena (X, Y).
                printf("Frequência da antena (letra): ");
                scanf(" %c", &freq); ///< Lê a frequência da antena.
                printf("Posição X: ");
                scanf("%d", &x); ///< Lê a posição X.
                printf("Posição Y: ");
                scanf("%d", &y); ///< Lê a posição Y.

                // Verifica se as posições estão dentro dos limites do mapa.
                if (x >= 0 && x < TAM_MAPA && y >= 0 && y < TAM_MAPA) {
                    inserirAntena(&lista, freq, x, y);
                    printf("Antena inserida!\n");
                } else {
                    printf("Posição inválida!\n");
                }
                break;
            }
            case 3: {
                // Remover uma antena da lista.
                int x, y; ///< Posições da antena a ser removida.
                printf("Posição X da antena a remover: ");
                scanf("%d", &x); ///< Lê a posição X da antena.
                printf("Posição Y da antena a remover: ");
                scanf("%d", &y); ///< Lê a posição Y da antena.
                removerAntena(&lista, x, y);
                break;
            }
            case 4:
                // Listar todas as antenas.
                listarAntenas(lista);
                break;
            case 5:
                // Deduzir as localizações com efeito nefasto.
                deduzirEfeitoNefasto(lista);
                break;
            case 6:
                // Mostrar o mapa com as antenas.
                mostrarMapa(lista);
                break;
            case 7:
                // Sair do programa.
                printf("Saindo...\n");
                break;
            default:
                // Caso o usuário insira uma opção inválida.
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 7); ///< O loop continua até o usuário escolher a opção de sair.

    liberarLista(lista); ///< Libera a memória alocada para as antenas.
    return 0; ///< Retorna 0 indicando que o programa foi executado com sucesso.
}
