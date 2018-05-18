#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);

double num_random() {
   double number = (double) random() / (double) RAND_MAX;
   if((double) random() / (double) RAND_MAX < 0.5) {
      number *= -1;
   }
   return number;
}

double omp_get_wtime();

int main(int argc, char* argv[]) {
   long int number_tosses, number_in_circle;
   int thread_count, i;
   double x, y, distance, start, end, elapsed;


   if (argc != 3) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   number_tosses = strtoll(argv[2], NULL, 10);
   if (thread_count < 1 || number_tosses < 1) Usage(argv[0]);

   number_in_circle =0;
   srandom(0);
   start = omp_get_wtime();
#  pragma omp parallel for num_threads(thread_count) \
      reduction(+: number_in_circle) private(x, y, distance)
   for (i = 0; i < number_tosses; i++) {
      x = num_random(); // generates between -1 e 1
      y = num_random();
      distance = x*x + y*y;

      if (distance <= 1) {
         number_in_circle += 1;
      }
   }
   end = omp_get_wtime();
   elapsed = end - start;

   double pi = 4*number_in_circle/((double) number_tosses);
   printf("Pi Estimation = %.14f\n", pi);
   printf("Time = %.14f\n", elapsed);
   return 0;
}  /* main */

void Usage(char* prog_name) {
   fprintf(stderr, "usage: %s <thread_count> <number_tosses>\n", prog_name);  /* Change */
   exit(0);
}  /* Usage */
