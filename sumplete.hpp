#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef struct cell
{
	int value;
	bool active;
} Cell;

class Sumplete
{
	int _size;
	vector<vector<Cell>> _cells;
	vector<int> _row_sums;
	vector<int> _column_sums;
	int sum_row(int) const;
	int sum_column(int) const;
	unsigned long max_width() const;
	public:
		Sumplete(vector<vector<int>>, vector<int>, vector<int>);
		Cell get_cell(int, int) const;
		int get_size() const;
		int get_row_sum(int) const;
		int get_column_sum(int) const;
		int energy();
		bool won();
		void flip(int, int);
		friend ostream &operator<<(ostream &, const Sumplete &);
};