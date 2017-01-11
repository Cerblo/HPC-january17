void
init_bounds(int size, double **u) {
int i;
for (i = 0; i < size; i++) {
u[i][0] = 0;
u[0][i] = 20;
u[i][size - 1] = 20;
u[size - 1][i] = 20;
}
}

void init_interior(int size, double **u, double guess) {
int i, j;
for (i = 1; i < size - 1; i++) {
	for (j = 1; j < size - 1; j++) {
		u[i][j] = guess;
	}
}
}

void
initialize(int size, double **u, double guess) {
init_bounds(size, u);
init_interior(size, u, guess);
//init_f(size);
}
