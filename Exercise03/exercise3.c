#include <omp.h>
#include <stdio.h>

int main() {

#pragma omp parallel
{
  int th = omp_get_thread_num();
  printf("thread # %d\n",th);
#pragma omp master
{
   printf("inside master # %d\n",omp_get_thread_num());
   printf("exiting master \n");
}
printf("hi again from thread # %d\n",omp_get_thread_num());
}
return 0;
}
