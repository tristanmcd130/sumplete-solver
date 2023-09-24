#include "sumplete.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double temperature(int);
double probability(double, double, double);

int main()
{
	srand(time(nullptr));
	int size;
	cout << "Size: ";
	cin >> size;
	vector<vector<int>> board;
	vector<int> row_sums;
	vector<int> column_sums;
	int temp;
	for(int i = 0; i < size; i++)
	{
		vector<int> row;
		cout << "Row " << i << ": ";
		for(int j = 0; j < size; j++)
		{
			cin >> temp;
			row.push_back(temp);
		}
		board.push_back(row);
	}
	cout << "Sums of rows: ";
	for(int i = 0; i < size; i++)
	{
		cin >> temp;
		row_sums.push_back(temp);
	}
	cout << "Sums of columns: ";
	for(int i = 0; i < size; i++)
	{
		cin >> temp;
		column_sums.push_back(temp);
	}
	Sumplete game(board, row_sums, column_sums);
	int step;
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
