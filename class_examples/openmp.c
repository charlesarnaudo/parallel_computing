#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);

int main(int argc, char const *argv[])
{
    int thread_count = strtol(argc[1], NULL, 10);
    # pragma omp parallel num_threads(thread_count)
    Hello();

    return 0;
}

void Hello(void) {
    int rank = omp_get_thread_num();
    int thread = omp_get_num_threads();

    printf("Hello from thread %d of %d\n", rank, thread);
}