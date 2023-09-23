#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "sumplete.hpp"

using namespace std;

double temperature(int);
double probability(double, double, double);

int main()
{
	srand(time(nullptr));
	int step;
	Sumplete game(9, -19, 19);
	for(step = 1; !game.won(); step++)
	{
		double temp = temperature(step);
		Sumplete new_game(game);
		new_game.flip(rand() % game.get_size(), rand() % game.get_size());
		if(probability(game.energy(), new_game.energy(), temp) >= (double)rand() / (double)RAND_MAX)
			game = new_game;
		if(step % 10000 == 0)
			cout << "Step: " << step << ", temperature: " << temp << ", energy: " << game.energy() << endl << game << endl;
	}
	cout << "Final step: " << step << endl << game;
	return 0;
}

double temperature(int step)
{
	return 2 / log(step + 0.01);
}

double probability(double energy, double new_energy, double temperature)
{
	if(new_energy <= energy)
		return 1.0;
	return exp((energy - new_energy) / temperature);
}
