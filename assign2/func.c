void
initialize(int size, double **u) {
int i;
for (i = 0; i < size; i++) {
u[i][size - 1] = 20;
u[i][0] = 0;
u[size - 1][i] = 20;
u[0][i] = 20;
}
}
