#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
// Suitable strip size aligning with SIMD vector boundaries (e.g., 256 or 512)
#define STRIP_SIZE 256

int main() {
    // Allocate arrays dynamically to handle 1,000,000 elements cleanly
    double *A = (double *)malloc(N * sizeof(double));
    double *B = (double *)malloc(N * sizeof(double));
    double *C = (double *)malloc(N * sizeof(double));

    if (!A || !B || !C) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        A[i] = 1.5;
        B[i] = 2.0;
        C[i] = 0.0;
    }

    double tstart, tstop, tcalc;
    tstart = omp_get_wtime();

    // 1. Strip mining: outer loop steps by STRIP_SIZE
    // 2. Parallelized across multiple threads using OpenMP
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i += STRIP_SIZE) {
        int limit = (i + STRIP_SIZE < N) ? (i + STRIP_SIZE) : N;
        // Inner strip loop processes elements sequentially within the chunk
        for (int j = i; j < limit; j++) {
            C[j] = A[j] * B[j];
        }
    }

    tstop = omp_get_wtime();
    tcalc = tstop - tstart;

    // Verification check
    printf("Verification: C[0] = %f, C[%d] = %f\n", C[0], N - 1, C[N - 1]);
    printf("Time taken: %f seconds\n", tcalc);

    free(A);
    free(B);
    free(C);

    return 0;
}
