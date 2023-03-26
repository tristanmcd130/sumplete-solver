#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "sumplete.h"

double temperature(int);
double probability(double, double, double);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int time_adjust = 0;
	Sumplete *game = sumplete_init(9, -19, 19);
	for(int time = 0; !sumplete_won(game); time++)
	{
		double temp = temperature(time);
		if(temp <= 0.125)
		{
			time_adjust += time;
			time = 0;
		}
		Sumplete *new_game = sumplete_copy(game);
		sumplete_choose(new_game, rand() % game->size, rand() % game->size);
		if(probability(sumplete_energy(game), sumplete_energy(new_game), temp) >= (double)rand() / (double)RAND_MAX)
		{
			sumplete_destroy(&game);
			game = sumplete_copy(new_game);
			printf("Time: %d, temperature: %lf, energy: %d\n", time + time_adjust, temp, sumplete_energy(game));
			sumplete_print(game);
		}
		sumplete_destroy(&new_game);
	}
	sumplete_destroy(&game);
	return 0;
}

double temperature(int time)
{
	return 2.0 / log(time + 1.01);
}

double probability(double energy, double new_energy, double temperature)
{
	if(new_energy <= energy)
		return 1.0;
	return exp((energy - new_energy) / temperature);
}
