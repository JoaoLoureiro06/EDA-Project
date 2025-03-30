/**
 * @file antenas.h
 * @brief Definição da estrutura e funções para gerenciamento de antenas.
 * 
 * Este arquivo contém as declarações das funções para manipular antenas, 
 * incluindo inserção, remoção, listagem e análise de interferências.
 */

 #ifndef ANTENAS_H
 #define ANTENAS_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <math.h>
 
 #define TAM_MAPA 12 ///< Tamanho do mapa de antenas.
 
 /**
  * @struct Antena
  * @brief Estrutura que representa uma antena.
  */
 typedef struct Antena {
     char freq;  ///< Frequência da antena.
     int x, y;   ///< Coordenadas X e Y da antena no mapa.
     struct Antena* next; ///< Ponteiro para a próxima antena na lista.
 } Antena;
 
 /**
  * @brief Cria uma nova antena.
  * @param freq Frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  * @return Ponteiro para a antena criada.
  */
 Antena* criarAntena(char freq, int x, int y);
 
 /**
  * @brief Insere uma antena na lista.
  * @param head Ponteiro para a cabeça da lista de antenas.
  * @param freq Frequência da antena.
  * @param x Coordenada X da antena.
  * @param y Coordenada Y da antena.
  */
 void inserirAntena(Antena** head, char freq, int x, int y);
 
 /**
  * @brief Remove uma antena da lista.
  * @param head Ponteiro para a cabeça da lista de antenas.
  * @param x Coordenada X da antena a ser removida.
  * @param y Coordenada Y da antena a ser removida.
  */
 void removerAntena(Antena** head, int x, int y);
 
 /**
  * @brief Carrega antenas de um arquivo.
  * @param head Ponteiro para a cabeça da lista de antenas.
  * @param nomeArquivo Nome do arquivo de onde carregar os dados.
  */
 void carregarAntenasDoArquivo(Antena** head, const char* nomeArquivo);
 
 /**
  * @brief Deduz locais com interferência no mapa.
  * @param head Ponteiro para a lista de antenas.
  */
 void deduzirEfeitoNefasto(Antena* head);
 
 /**
  * @brief Lista todas as antenas registradas.
  * @param head Ponteiro para a lista de antenas.
  */
 void listarAntenas(Antena* head);
 
 /**
  * @brief Exibe o mapa com as antenas.
  * @param head Ponteiro para a lista de antenas.
  */
 void mostrarMapa(Antena* head);
 
 /**
  * @brief Libera a memória alocada para a lista de antenas.
  * @param head Ponteiro para a lista de antenas.
  */
 void liberarLista(Antena* head);
 
 #endif // ANTENAS_H
 