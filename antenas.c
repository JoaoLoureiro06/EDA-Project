#include "antenas.h"

/**
 * @brief Cria uma nova antena.
 * 
 * Função responsável por alocar memória e inicializar os valores de uma nova antena.
 * 
 * @param freq Frequência da antena.
 * @param x Coordenada X da posição da antena.
 * @param y Coordenada Y da posição da antena.
 * @return Retorna um ponteiro para a nova antena criada.
 */
Antena* criarAntena(char freq, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    nova->freq = freq;
    nova->x = x;
    nova->y = y;
    nova->next = NULL;
    return nova;
}

/**
 * @brief Insere uma nova antena na lista.
 * 
 * Esta função insere uma nova antena na lista de antenas, no início da lista.
 * 
 * @param head Ponteiro para o ponteiro da lista de antenas.
 * @param freq Frequência da antena.
 * @param x Coordenada X da posição da antena.
 * @param y Coordenada Y da posição da antena.
 */
void inserirAntena(Antena** head, char freq, int x, int y) {
    Antena* nova = criarAntena(freq, x, y);
    nova->next = *head;
    *head = nova;
}

/**
 * @brief Remove uma antena da lista.
 * 
 * Esta função remove uma antena específica da lista, com base nas suas coordenadas X e Y.
 * 
 * @param head Ponteiro para o ponteiro da lista de antenas.
 * @param x Coordenada X da posição da antena a ser removida.
 * @param y Coordenada Y da posição da antena a ser removida.
 */
void removerAntena(Antena** head, int x, int y) {
    Antena* temp = *head;
    Antena* prev = NULL;

    while (temp != NULL && (temp->x != x || temp->y != y)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Antena não encontrada na posição (%d, %d)!\n", x, y);
        return;
    }

    if (prev == NULL) { 
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Antena removida com sucesso!\n");
}

/**
 * @brief Carrega antenas a partir de um arquivo.
 * 
 * Esta função lê as antenas de um arquivo e as insere na lista.
 * O arquivo deve conter as antenas em um formato específico.
 * 
 * @param head Ponteiro para o ponteiro da lista de antenas.
 * @param nomeArquivo Nome do arquivo a ser carregado.
 */
void carregarAntenasDoArquivo(Antena** head, const char* nomeArquivo) {
    FILE* file = fopen(nomeArquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[100];
    int x = 0;
    while (fgets(linha, sizeof(linha), file) && x < TAM_MAPA) {
        for (int y = 0; y < strlen(linha); y++) {
            char freq = linha[y];
            if (freq != '\n' && freq != '.') { // Ignora pontos e novas linhas
                inserirAntena(head, freq, x, y);
            }
        }
        x++;
    }

    fclose(file);
    printf("Antenas carregadas com sucesso!\n");
}

/**
 * @brief Deduz as localizações com efeito nefasto.
 * 
 * A função verifica as antenas na lista e, caso haja interferência entre duas antenas da mesma frequência,
 * marca o ponto médio entre elas com um efeito nefasto.
 * 
 * @param head Ponteiro para a lista de antenas.
 */
void deduzirEfeitoNefasto(Antena* head) {
    char mapa[TAM_MAPA][TAM_MAPA];

    // Inicializa o mapa com pontos
    for (int i = 0; i < TAM_MAPA; i++) {
        for (int j = 0; j < TAM_MAPA; j++) {
            mapa[i][j] = '.';
        }
    }

    // Coloca as antenas no mapa
    Antena* temp = head;
    while (temp != NULL) {
        mapa[temp->x][temp->y] = temp->freq;
        temp = temp->next;
    }

    // Verifica pares de antenas para interferência
    for (Antena* ant1 = head; ant1 != NULL; ant1 = ant1->next) {
        for (Antena* ant2 = ant1->next; ant2 != NULL; ant2 = ant2->next) {
            if (ant1->freq == ant2->freq) { 
                int dx = ant2->x - ant1->x;
                int dy = ant2->y - ant1->y;

                //  alinhamento (horizontal, vertical, diagonal)
                if (dx == 0 || dy == 0 || abs(dx) == abs(dy)) {
             
                    int dist1 = sqrt(dx * dx + dy * dy);
                    int dist2 = dist1 / 2; // A distância entre uma antena e o ponto médio

                    // Condição: uma antena está a duas vezes a distância da outra
                    int mx = (ant1->x + ant2->x) / 2;
                    int my = (ant1->y + ant2->y) / 2;

                    // Verifica se a localização do efeito nefasto é válida
                    if (dist1 == 2 * dist2 && mx >= 0 && mx < TAM_MAPA && my >= 0 && my < TAM_MAPA && mapa[mx][my] == '.') {
                        mapa[mx][my] = '#'; 
                    }
                }
            }
        }
    }

    printf("\nMapa com Localizações com Efeito Nefasto:\n");
    for (int i = 0; i < TAM_MAPA; i++) {
        for (int j = 0; j < TAM_MAPA; j++) {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}



/**
 * @brief Lista todas as antenas registradas.
 * 
 * Função que percorre a lista de antenas e exibe as informações de cada uma.
 * 
 * @param head Ponteiro para a lista de antenas.
 */
void listarAntenas(Antena* head) {
    if (head == NULL) {
        printf("Nenhuma antena registrada.\n");
        return;
    }

    printf("\nAntenas registradas:\n");
    while (head != NULL) {
        printf("Frequência: %c | Posição: (%d, %d)\n", head->freq, head->x, head->y);
        head = head->next;
    }
}

/**
 * @brief Mostra o mapa com as antenas registradas.
 * 
 * Esta função exibe um mapa com as antenas representadas por suas respectivas frequências.
 * 
 * @param head Ponteiro para a lista de antenas.
 */
void mostrarMapa(Antena* head) {
    char mapa[TAM_MAPA][TAM_MAPA];

    // Inicializa o mapa com pontos
    for (int i = 0; i < TAM_MAPA; i++) {
        for (int j = 0; j < TAM_MAPA; j++) {
            mapa[i][j] = '.';
        }
    }

    // Coloca as antenas no mapa
    Antena* temp = head;
    while (temp != NULL) {
        if (temp->x >= 0 && temp->x < TAM_MAPA && temp->y >= 0 && temp->y < TAM_MAPA) {
            mapa[temp->x][temp->y] = temp->freq;
        }
        temp = temp->next;
    }

    printf("\nMapa das antenas:\n");
    for (int i = 0; i < TAM_MAPA; i++) {
        for (int j = 0; j < TAM_MAPA; j++) {
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief Libera a memória alocada pela lista de antenas.
 * 
 * Esta função percorre toda a lista de antenas e libera a memória alocada para cada antena.
 * 
 * @param head Ponteiro para a lista de antenas.
 */
void liberarLista(Antena* head) {
    Antena* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
