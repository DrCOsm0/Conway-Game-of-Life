/**
 * @file life.c
 * 
 * @brief Conway's Game of Life (functions)
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


#include "life.h"
#include <stdio.h>
#include <stdlib.h>


/** prints a given 2D matrix
 * @param matrix matrix to print
 * @param m_row number of rows in the matrix
 * @param m_col number of colums in the matrix
 */
void print_matrix(unsigned char **matrix, int m_row, int n_col)
{
    for(int i = 0; i < m_row; i++)
        for(int j = 0; j < n_col; j++)
            printf(j == n_col - 1 ? "%d\n" : "%d ", matrix[i][j]);
}

/** initializes a matrix of given rows and colums to 0
 * @return the initialized matrix
 * @param m_row number of rows in the matrix
 * @param m_col number of colums in the matrix
 */
unsigned char **init_matrix(int m_row, int n_col)
{

    unsigned char **a;

    a = malloc(m_row * sizeof(unsigned char *));
    if(!a)
        return NULL;
    for(int i = 0; i < m_row; i++)
    {
        a[i] = malloc(n_col * sizeof(unsigned char));
        if(!a[i])
        {
            for(int j = 0; j < i; j++)
                free(a[j]);
            free(a);
            return NULL;
        }
    }
    return a;
}

/** sets a given bit to 1 in a matrix
 * @return the modified matrix
 * @param m_row number of rows in the matrix
 * @param m_col number of colums in the matrix
 * @param matrix the matrix to modify
 */
unsigned char **set_bit(unsigned char **matrix, int row, int col)
{
    matrix[row][col] = 1;
    return matrix;
}

/** sets a given bit to 0 in a matrix
 * @return the modified matrix
 * @param m_row number of rows in the matrix
 * @param m_col number of colums in the matrix
 * @param matrix the matrix to modify
 */
unsigned char **clear_bit(unsigned char **matrix, int row, int col)
{
    matrix[row][col] = 0;
    return matrix;
}

/** counts the number of alive cells in a hedge edge type
 * @return the number of alive cells
 * @param bound_width the width of the board(playing field)
 * @param bound_height the height of the board(playing field)
 * @param matrix the current generation matrix
 * @param x the x coordinate of the matrix location
 * @param y the y coordinate of the matrix location
 */
int count_neighbors_hedge(unsigned char **matrix, int bound_width, int bound_height, int x, int y)
{
    int i, j, count = 0;
    
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if (!(i == 0 && j == 0) && (x + i >= 0 && x + i < bound_height) && (y + j >= 0 && y + j < bound_width) && matrix[x + i][y + j] == 1)
                count++;
    return count;
}

/** counts the number of alive cells in a torus edge type
 * @return the number of alive cells
 * @param bound_width the width of the board(playing field)
 * @param bound_height the height of the board(playing field)
 * @param matrix the current generation matrix
 * @param x the x coordinate of the matrix location
 * @param y the y coordinate of the matrix location
 */
int count_neighbors_torus(unsigned char **matrix, int bound_width, int bound_height, int x, int y)
{
    int i, j, count = 0;
    
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if(!(i == 0 && j == 0) && matrix[(x + i + bound_width) % bound_width][(y + j + bound_height) % bound_height] == 1)
                count++;
    return count;
}

/** counts the number of alive cells in a klein edge type
 * @return the number of alive cells
 * @param bound_width the width of the board(playing field)
 * @param bound_height the height of the board(playing field)
 * @param matrix the current generation matrix
 * @param x the x coordinate of the matrix location
 * @param y the y coordinate of the matrix location
 */
int count_neighbors_klein(unsigned char **matrix, int bound_width, int bound_height, int x, int y)
{
    int i, j, count = 0;
    
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if(!(i == 0 && j == 0) && matrix[(x + i + bound_width) % bound_width][(y + j + bound_height) % bound_height] == 1)
                count++;
    return count;
}

/** sets the state of the new generation of cells in the matrix.
 * @return the modifyed matrix after rules are applied
 * @param a the prevoius generation of cells
 * @param b the current generation of cells
 * @param n_neighbors number of alive neighbors
 * @param x the x coordinate of the current cell
 * @param y the y coordinate of the current cell
 */
unsigned char **set_state(unsigned char **a, unsigned char **b, int x, int y, int n_neighbors)
{
    int current_state = a[x][y];
    
    if (current_state == 1 && n_neighbors < 2)
        clear_bit(b, x, y);
    else if (current_state == 1 && n_neighbors > 3)
        clear_bit(b, x, y);
    else if (current_state == 1 && (n_neighbors == 2 || n_neighbors == 3))
        set_bit(b, x, y);
    else if (current_state == 0 && n_neighbors == 3)
        set_bit(b, x, y);
    else
        clear_bit(b, x, y);

    return b;
}

/** copys matrix b back to matrix a
 * @return matrix a
 * @param a the new matrix copied to
 * @param b the old matrix being copied from
 * @param width width of the matrix
 * @param height height of the matrix
 */
unsigned char **copy_board(unsigned char **a, unsigned char **b, int width, int height)
{

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            a[i][j] = b[i][j];
    
    return a;
}

/** frees the allocated memory of a matrix
 * @param matrix the matrix being freed
 * @param b the number of rows of the matrix
 */
void free_matrix(unsigned char **matrix, int m_row)
{
    for(int i = 0; i < m_row; i++)
                free(matrix[i]);
            free(matrix);
}
