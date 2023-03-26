#include <stdlib.h>
#include <stdio.h>
#include "sumplete.h"

int sumplete_sum_row(Sumplete *game, int row)
{
	int sum = 0;
	for(int col = 0; col < game->size; col++)
		sum += game->cells[row * game->size + col].value * game->cells[row * game->size + col].active;
	return sum;
}

int sumplete_sum_col(Sumplete *game, int col)
{
	int sum = 0;
	for(int row = 0; row < game->size; row++)
		sum += game->cells[row * game->size + col].value * game->cells[row * game->size + col].active;
	return sum;
}

Sumplete *sumplete_init(int size, int low, int high)
{
	Sumplete *game = (Sumplete *)malloc(sizeof(Sumplete));
	if(game != NULL)
	{
		game->size = size;
		game->cells = (Cell *)malloc(size * size * sizeof(Cell));
		if(game->cells == NULL)
		{
			printf("Error allocating array of cells\n");
			return NULL;
		}
		for(int i = 0; i < size * size; i++)
		{
			do {
				game->cells[i].value = rand() % (high - low + 1) + low;
			} while(game->cells[i].value == 0);
			game->cells[i].active = rand() % 2;
		}
		game->row_sums = (int *)malloc(size * sizeof(int));
		if(game->row_sums == NULL)
		{
			printf("Error allocating array of sums\n");
			return NULL;
		}
		for(int row = 0; row < size; row++)
			game->row_sums[row] = sumplete_sum_row(game, row);
		game->col_sums = (int *)malloc(size * sizeof(int));
		if(game->col_sums == NULL)
		{
			printf("Error allocating array of sums\n");
			return NULL;
		}
		for(int col = 0; col < size; col++)
			game->col_sums[col] = sumplete_sum_col(game, col);
		for(int i = 0; i < size * size; i++)
			game->cells[i].active = TRUE;
	}
	return game;
}

Sumplete *sumplete_copy(Sumplete *original)
{
	Sumplete *copy = sumplete_init(original->size, 1, 1);
	if(copy != NULL)
	{
		for(int i = 0; i < original->size * original->size; i++)
			copy->cells[i] = original->cells[i];
		for(int i = 0; i < original->size; i++)
		{
			copy->row_sums[i] = original->row_sums[i];
			copy->col_sums[i] = original->col_sums[i];
		}
	}
	return copy;
}

int sumplete_energy(Sumplete *game)
{
	int energy = game->size * 2;
	for(int row = 0; row < game->size; row++)
	{
		if(sumplete_sum_row(game, row) == game->row_sums[row])
			energy--;
	}
	for(int col = 0; col < game->size; col++)
	{
		if(sumplete_sum_col(game, col) == game->col_sums[col])
			energy--;
	}
	return energy;
}

boolean sumplete_won(Sumplete *game)
{
	return sumplete_energy(game) == 0;
}

void sumplete_choose(Sumplete *game, int row, int col)
{
	game->cells[row * game->size + col].active = !game->cells[row * game->size + col].active;
}

boolean sumplete_equal(Sumplete *game_a, Sumplete *game_b)
{
	if(game_a->size != game_b->size)
		return FALSE;
	for(int i = 0; i < game_a->size * game_a->size; i++)
	{
		if(game_a->cells[i].value != game_b->cells[i].value || game_a->cells[i].active != game_b->cells[i].active)
			return FALSE;
	}
	for(int i = 0; i < game_a->size; i++)
	{
		if(game_a->row_sums[i] != game_b->row_sums[i] || game_a->col_sums[i] != game_b->col_sums[i])
			return FALSE;
	}
	return TRUE;
}

void sumplete_print(Sumplete *game)
{
	for(int row = 0; row < game->size; row++)
	{
		for(int col = 0; col < game->size; col++)
		{
			if(!game->cells[row * game->size + col].active)
				printf("\x1B[0;31m");
			printf("%5d\x1B[0m", game->cells[row * game->size + col].value);
		}
		printf(" |");
		if(sumplete_sum_row(game, row) != game->row_sums[row])
			printf("\x1B[0;90m");
		printf("%5d\x1B[0m\n", game->row_sums[row]);
	}
	for(int i = 0; i < game->size * 5 + 1; i++)
		printf("-");
	printf("+\n");
	for(int col = 0; col < game->size; col++)
	{
		if(sumplete_sum_col(game, col) != game->col_sums[col])
			printf("\x1B[0;90m");
		printf("%5d\x1B[0m", game->col_sums[col]);
	}
	printf("\n\n");
}

void sumplete_destroy(Sumplete **p_game)
{
	free((*p_game)->cells);
	free((*p_game)->row_sums);
	free((*p_game)->col_sums);
	free(*p_game);
	*p_game = NULL;
}
