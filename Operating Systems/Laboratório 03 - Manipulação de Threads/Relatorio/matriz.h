/**
 * Header: matriz.h
 * Descrição: funções básicas para manipular matriz dinâmica
 * 
 * Autor: Rodrigo Campiolo
 * Data: 04/09/2019
 */

/** cria uma matriz de inteiros row x col **/
int** create_matrix(int row, int col);

/* gera elementos inteiros para uma matriz row x col existente */
void generate_elements(int** matrix, int row, int col, int limit);

/* lê uma matriz de um arquivo - row e col são configurados a partir do arquivo */
int** read_matrix_from_file(char* filename, int *row, int *col);

/*  exibe uma matrix row x col */
void print_matrix(int** matrix, int row, int col);