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
init_f(int N, double **f) {
int i,j, i_min, i_max, j_min, j_max;
i_min = (N + 1) / 2. * (0 + 1);
i_max = (N + 1) / 2. * (1. / 3 + 1);
j_max = (N + 1) / 2. * ( - 1. / 3 + 1);
j_min = (N + 1) / 2. * (- 2. / 3 + 1);

for (i = i_min; i <= i_max; i++) {
	for (j = j_min; j <= j_max; j++) {
		f[i][j] = 200.;
	}
}
}


void
init_u(int size, double **u, double guess) {
init_bounds(size, u);
init_interior(size, u, guess);
}
