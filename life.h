/**
 * @file life.h
 * 
 * @brief Conway's Game of Life (header file)
 * 
 * @details This program uses seven major functions to recreate Conway's Game of Life.
 * This program has edge functionality including torus, hedge, and klein bottle edge behavior.
 * The program renders an SDL window to run the game and has custom functionality to allow
 * the user to set window size, pixle color, and starting life form position and source file.
 * 
 * @author Jainder Bhullar
 * 
 * @date 11/26/2020
 *
 * @todo none
 *
 * @bug no bugs so far :)
 *
 * 
 */


#ifndef LIFE_H_
#define LIFE_H_

void print_matrix(unsigned char **matrix, int m_row, int n_col);
unsigned char **init_matrix(int m_row, int n_col);
unsigned char **set_bit(unsigned char **matrix, int row, int col);
unsigned char **clear_bit(unsigned char **matrix, int row, int col);
int count_neighbors_hedge(unsigned char **matrix, int bound_width, int bound_height, int x, int y);
int count_neighbors_torus(unsigned char **matrix, int bound_width, int bound_height, int x, int y);
int count_neighbors_klein(unsigned char **matrix, int bound_width, int bound_height, int x, int y);
unsigned char **set_state(unsigned char **a, unsigned char **b, int x, int y, int n_neighbors);
unsigned char **copy_board(unsigned char **a, unsigned char **b, int width, int height);
void free_matrix(unsigned char **matrix, int m_row);


#endif
