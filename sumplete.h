#pragma once

typedef enum {FALSE, TRUE} boolean;
typedef struct cell {
	int value;
	boolean active;
} Cell;
typedef struct sumplete {
	int size;
	Cell *cells;
	int *row_sums;
	int *col_sums;
} Sumplete;

int sumplete_sum_row(Sumplete *, int);
int sumplete_sum_col(Sumplete *, int);
Sumplete *sumplete_init(int, int, int);
Sumplete *sumplete_copy(Sumplete *);
int sumplete_energy(Sumplete *);
boolean sumplete_won(Sumplete *);
void sumplete_choose(Sumplete *, int, int);
boolean sumplete_equal(Sumplete *, Sumplete *);
void sumplete_print(Sumplete *);
void sumplete_destroy(Sumplete **);
