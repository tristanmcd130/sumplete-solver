#include "sumplete.hpp"
#include <iomanip>

using namespace std;

Sumplete::Sumplete(vector<vector<int>> board, vector<int> row_sums, vector<int> column_sums): _size(board.size()), _row_sums(row_sums), _column_sums(column_sums)
{
	for(int i = 0; i < board.size(); i++)
	{
		vector<Cell> row;
		for(int j = 0; j < board.size(); j++)
			row.push_back({board.at(i).at(j), true});
		_cells.push_back(row);
	}
}

Cell Sumplete::get_cell(int row, int column) const
{
	return _cells.at(row).at(column);
}

int Sumplete::get_size() const
{
	return _size;
}

int Sumplete::get_row_sum(int row) const
{
	return _row_sums.at(row);
}

int Sumplete::get_column_sum(int column) const
{
	return _column_sums.at(column);
}

int Sumplete::sum_row(int row) const
{
	int sum = 0;
	for(int i = 0; i < _size; i++)
		sum += _cells.at(row).at(i).value * _cells.at(row).at(i).active;
	return sum;
}

int Sumplete::sum_column(int column) const
{
	int sum = 0;
	for(int i = 0; i < _size; i++)
		sum += _cells.at(i).at(column).value * _cells.at(i).at(column).active;
	return sum;
}

int Sumplete::energy()
{
	int energy = _size * 2;
	for(int i = 0; i < _size; i++)
	{
		if(sum_row(i) == _row_sums.at(i))
			energy--;
		if(sum_column(i) == _column_sums.at(i))
			energy--;
	}
	return energy;
}

bool Sumplete::won()
{
	return energy() == 0;
}

void Sumplete::flip(int row, int column)
{
	_cells.at(row).at(column).active = !_cells.at(row).at(column).active;
}

unsigned long Sumplete::max_width() const
{
	unsigned long max_width = 0;
	for(int i = 0; i < _size; i++)
	{
		for(int j = 0; j < _size; j++)
			max_width = max(max_width, to_string(_cells.at(i).at(j).value).size() + 1);
	}
	for(int i = 0; i < _size; i++)
	{
		max_width = max(max_width, to_string(_row_sums.at(i)).size() + 1);
		max_width = max(max_width, to_string(_column_sums.at(i)).size() + 1);
	}
	return max_width;
}

ostream &operator<<(ostream &out, const Sumplete &game)
{
	for(int i = 0; i < game._size; i++)
	{
		for(int j = 0; j < game._size; j++)
		{
			out << "\x1B[0m" << (game._cells.at(i).at(j).active ? "" : "\x1B[31m") << setw(game.max_width()) << game._cells.at(i).at(j).value;
		}
		out << "\x1B[0m\x1B[1m" << (game.sum_row(i) == game._row_sums.at(i) ? "" : "\x1B[90m") << setw(game.max_width()) << game._row_sums.at(i) << endl;
	}
	for(int i = 0; i < game._size; i++)
		out << "\x1B[0m\x1B[1m" << (game.sum_column(i) == game._column_sums.at(i) ? "" : "\x1B[90m") << setw(game.max_width()) << game._column_sums.at(i);
	return out << "\x1B[0m" << endl;
}