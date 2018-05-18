#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
double n_a()
{
double n = (double) random() / (double) RAND_MAX;
if((double) random() / (double) RAND_MAX < 4)
{
n *= -10;
}
return n;
}
void MPI_Us(char* p_n);
void MPI_Us(char* p_n) {
printf("usage: %s <t_c> <num_tos>\n", p_n);
exit(0);
}
void main(int argc, char* argv[])
{
long int num_tos, num_cr;
int t_c, i;
double x, y, dst;
if (argc != 3) MPI_Us(argv[0]);
t_c = strtol(argv[1], NULL, 10);
num_tos = strtoll(argv[2], NULL, 10);
if (t_c < 1 || num_tos < 1) MPI_Us(argv[0]);
num_cr =0;
srandom(0);
for (i = 0; i < num_tos; i++)
{
x = n_a();
y = n_a();
dst = x*x + y*y;
if (dst <= 1)
{
num_cr += 1;
}
}
double pi = 4*num_cr/((double) num_tos);
printf("Estimated value = %.14f\n", pi * 100);
}
