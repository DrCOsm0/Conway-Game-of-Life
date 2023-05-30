/**
 * @file gl.c
 * 
 * @brief Conway's Game of Life (main)
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

#include <stdlib.h>
#include "sdl.h"
#include "life.h"
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int width = 400;  
	int height = 400;   
	int sprite_size = 4; /* either 2, 4, 8, or 16 */
	int orgin_x = 50;
	int orgin_y = 50;
	int file_input_x;
	int file_input_y;
	int opt;
	int edge_flag = 1;

	char *life_file = NULL;

	

    unsigned char **a;
	unsigned char **b;
	
	unsigned char red = 255;
	unsigned char green = 255;
	unsigned char blue = 255;
        struct sdl_info_t sdl_info; /* this is needed to graphically display the game */

	

	while((opt = getopt(argc, argv, "w:h:r:g:b:s:f:o:e:H")) != -1)
	{
		switch(opt)
		{
			case 'w':
				width = atoi(optarg);
				break;
			
			case 'h':
				height = atoi(optarg);
				break;
			
			case 'r':
				red = atoi(optarg);
				break;

			case 'g':
				green = atoi(optarg);
				break;

			case 'b':
				blue = atoi(optarg);
				break;

			case 's':
				sprite_size = atoi(optarg);
				break;
			
			case 'f':
				life_file = optarg;
				break;
			
			case 'o': ;
				char *c = optarg;
				char *token = strtok(c, ",");
				orgin_x = atoi(token);
				token = strtok(NULL, "");
				orgin_y = atoi(token);
				break;

			case 'e': ;
				char *hedge = "hedge";
				char *torus = "torus";
				char *klein = "klein";

				if(strcmp(hedge, optarg) == 0)
					edge_flag = 1;

				if(strcmp(torus, optarg) == 0)
					edge_flag = 2;

				if(strcmp(klein, optarg) == 0)
					edge_flag = 3;

				break;
			
			case 'H':
				printf("-w width of the screen argument 640, 800, 1024, etc.\n\n");
				printf("-h height of the screen argument 480, 600, 768, etc.\n\n");
				printf("-e type of edge. Values are hedge, torus or klein (strings)\n\n");
				printf("-r the red color value, an integer between [0, 255]\n\n");
				printf("-g the green color value, an integer between [0, 255]\n\n");
				printf("-b the blue color value, an integer between [0, 255]\n\n");
				printf("-s size of the sprite. Valid values are 2, 4, 8, or 16 only. An integer.\n\n");
				printf("-f filename, a life pattern in file format 1.06.\n\n");
				printf("-o x,y the initial x,y coordinate of the pattern found in the file. No space between the x and y.\n\n");
		}
	}

	int bound_width = width / sprite_size;  
	int bound_height = height /sprite_size;  
	FILE *file = fopen(life_file, "r");

	if(file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

	a = init_matrix(width, height);
	b = init_matrix(width, height);
	init_sdl_info(&sdl_info, width, height, sprite_size, red, green, blue);

	fscanf(file, "%*[^\n]\n");
	while(fscanf(file, "%d %d", &file_input_x, &file_input_y) != EOF)
		set_bit(a, orgin_x + file_input_x, orgin_y + file_input_y);

	fclose(file);
	
	
	while (1)
	{
		if (SDL_GetTicks() % 1 == 0) {

			switch(edge_flag)
			{
				case 1:
					for (int y = 0; y < height; y++)
        				for (int x = 0; x < width; x++)
						{
							int alive = count_neighbors_hedge(a, bound_width, bound_height, x, y);
							b = set_state(a, b, x, y, alive);
						}
				break;

				case 2:
					for (int y = 0; y < height; y++)
        				for (int x = 0; x < width; x++)
						{
							int alive = count_neighbors_torus(a, bound_width, bound_height, x, y);
							b = set_state(a, b, x, y, alive);
						}
				break;

				case 3:
					for (int y = 0; y < height; y++)
        				for (int x = 0; x < width; x++)
						{
							int alive = count_neighbors_klein(a, bound_width, bound_height, x, y);
							b = set_state(a, b, x, y, alive);
						}
				break;
			}

			a = copy_board(a, b, width, height);
			sdl_render_life(&sdl_info,a);
		}	

                
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
			case SDL_KEYDOWN:
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					free_matrix(a, width);
					free_matrix(b, width);
					printf("Thats Life Folks!\n");
					return 0;
				}
				break;
			case SDL_QUIT:
				free_matrix(a, width);
				free_matrix(b, width);
				printf("Thats Life Folks!\n");
				return(0);
			}
		}
	}
}
