#include <stdio.h>
#include <omp.h>
#include <math.h>

#define N 100000



double result = 0.0;

double countPi();

int main() {
    int num;
    int threadId;

    int threadsNum = 4;
    omp_set_num_threads(threadsNum);

    unsigned int val = 0;

    int a[N], b[N], c[N];

    double runTime = omp_get_wtime();

    double pi;

    #pragma omp parallel
    {

        num = omp_get_num_threads();
        threadId = omp_get_thread_num();
        printf("num: %d threadId: %d\n", num, threadId);

        val++;
	int i;
        #pragma omp for
        for (i = 0; i < N; i++){
            a[i] = i;
            b[i] = N - i;
            c[i] = a[i] + b[i];

        }

        pi = countPi();

    }

    double endTime = omp_get_wtime();

    printf("c[0]: %d\n", c[0]);
    printf("c[1]: %d\n", c[1]);
    printf("val: %d\n", val);

    printf("runTime: %f\n", runTime);
    printf("endTime: %f\n", endTime);
    printf("subTime: %f\n", endTime - runTime);

    printf("pi: %f\n", pi);

    return 0;

}


double countPi(){
    int i = 0;

    #pragma omp for
    for (i = 0; i < N; i++)
    {
        result += 2 * sqrt(3) * pow(-1, i) / (pow(3, i) * (2 * i + 1));
    }


    return result;
}
