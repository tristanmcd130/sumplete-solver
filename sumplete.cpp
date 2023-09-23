#include <iomanip>
#include "sumplete.hpp"

using namespace std;

Sumplete::Sumplete(int size, int low, int high)
{
	_size = size;
	_cells = new Cell*[size];
	for(int i = 0; i < size; i++)
	{
		_cells[i] = new Cell[size];
		for(int j = 0; j < size; j++)
		{
			do {
				_cells[i][j].value = rand() % (high - low + 1) + low;
			} while(_cells[i][j].value == 0);
			// set every cell randomly to on or off to come up with the target row/col sums, then turn them all on
			_cells[i][j].active = rand() % 2;
		}
	}
	_row_sums = new int[size];
	for(int i = 0; i < size; i++)
		_row_sums[i] = sum_row(i);
	_column_sums = new int[size];
	for(int i = 0; i < size; i++)
		_column_sums[i] = sum_column(i);
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			_cells[i][j].active = true;
	}
}

Sumplete::Sumplete(const Sumplete &game)
{
	_size = game.get_size();
	_cells = new Cell*[_size];
	for(int i = 0; i < _size; i++)
	{
		_cells[i] = new Cell[_size];
		for(int j = 0; j < _size; j++)
			_cells[i][j] = game.get_cell(i, j);
	}
	_row_sums = new int[_size];
	for(int i = 0; i < _size; i++)
		_row_sums[i] = game.get_row_sum(i);
	_column_sums = new int[_size];
	for(int i = 0; i < _size; i++)
		_column_sums[i] = game.get_column_sum(i);
}

Sumplete::~Sumplete()
{
	for(int i = 0; i < _size; i++)
		delete[] _cells[i];
	delete[] _cells;
	delete[] _row_sums;
	delete[] _column_sums;
}

Sumplete &Sumplete::operator=(const Sumplete &game)
{
	this->~Sumplete(); // maybe not ideal way to do this but it does what i need it to do
	_size = game.get_size();
	_cells = new Cell*[_size];
	for(int i = 0; i < _size; i++)
	{
		_cells[i] = new Cell[_size];
		for(int j = 0; j < _size; j++)
			_cells[i][j] = game.get_cell(i, j);
	}
	_row_sums = new int[_size];
	for(int i = 0; i < _size; i++)
		_row_sums[i] = game.get_row_sum(i);
	_column_sums = new int[_size];
	for(int i = 0; i < _size; i++)
		_column_sums[i] = game.get_column_sum(i);
	return *this;
}

Cell Sumplete::get_cell(int row, int column) const
{
	return _cells[row][column];
}

int Sumplete::get_size() const
{
	return _size;
}

int Sumplete::get_row_sum(int row) const
{
	return _row_sums[row];
}

int Sumplete::get_column_sum(int column) const
{
	return _column_sums[column];
}

int Sumplete::sum_row(int row) const
{
	int sum = 0;
	for(int i = 0; i < _size; i++)
		sum += _cells[row][i].value * _cells[row][i].active;
	return sum;
}

int Sumplete::sum_column(int column) const
{
	int sum = 0;
	for(int i = 0; i < _size; i++)
		sum += _cells[i][column].value * _cells[i][column].active;
	return sum;
}

int Sumplete::energy()
{
	int energy = _size * 2;
	for(int i = 0; i < _size; i++)
	{
		if(sum_row(i) == _row_sums[i])
			energy--;
		if(sum_column(i) == _column_sums[i])
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
	_cells[row][column].active = !_cells[row][column].active;
}

unsigned long Sumplete::max_width() const
{
	unsigned long max_width = 0;
	for(int i = 0; i < _size; i++)
	{
		for(int j = 0; j < _size; j++)
			max_width = max(max_width, to_string(_cells[i][j].value).size() + 1);
	}
	for(int i = 0; i < _size; i++)
	{
		max_width = max(max_width, to_string(_row_sums[i]).size() + 1);
		max_width = max(max_width, to_string(_column_sums[i]).size() + 1);
	}
	return max_width;
}

ostream &operator<<(ostream &out, const Sumplete &game)
{
	for(int i = 0; i < game._size; i++)
	{
		for(int j = 0; j < game._size; j++)
		{
			out << "\x1B[0m" << (game._cells[i][j].active ? "" : "\x1B[31m") << setw(game.max_width()) << game._cells[i][j].value;
		}
		out << "\x1B[0m\x1B[1m" << (game.sum_row(i) == game._row_sums[i] ? "" : "\x1B[90m") << setw(game.max_width()) << game._row_sums[i] << endl;
	}
	for(int i = 0; i < game._size; i++)
		out << "\x1B[0m\x1B[1m" << (game.sum_column(i) == game._column_sums[i] ? "" : "\x1B[90m") << setw(game.max_width()) << game._column_sums[i];
	return out << "\x1B[0m" << endl;
}
