#pragma once
#include <iostream>

using std::ostream;

typedef struct cell
{
	int value;
	bool active;
} Cell;

class Sumplete
{
	int _size;
	Cell **_cells;
	int *_row_sums;
	int *_column_sums;
	int sum_row(int) const;
	int sum_column(int) const;
	unsigned long max_width() const;
	public:
		Sumplete(int, int, int);
		Sumplete(const Sumplete &);
		~Sumplete();
		Sumplete &operator=(const Sumplete &);
		Cell get_cell(int, int) const;
		int get_size() const;
		int get_row_sum(int) const;
		int get_column_sum(int) const;
		int energy();
		bool won();
		void flip(int, int);
		friend ostream &operator<<(ostream &, const Sumplete &);
};
