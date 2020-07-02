//
//  main.cpp
//  N
//
//  Created by macbook on 25.05.2020.
//  Copyright © 2020 macbook. All rights reserved.
//
//
//

#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <ctime>


class potok_name {
public:
    int id = 0;
    double size = 0;
    unsigned int time = 0;
    pthread_mutex_t *mutex = NULL;
};

//thread function
void* potok (void *array);

//integral function
inline double integ(double x, double dx);


double SUM = 0;
double dX = 0.001;

int main (int argc, char *argv[])
{
    
    double cut = 0;
    double size = 0;
    unsigned int BOSStime = 0;
    
    
    printf("\n\nEnter the integration segment:\n");
    scanf("%lg",&cut);
    printf("\nYou entered cut = %lg\nEnter the size of the integration parts:\n", cut);
    scanf("%lg",&size);
    printf("\nYou entered size = %lg\n",size);
    
    
    //Time of the entire program
    //1
    BOSStime = clock();
    
    //check: if the part size is larger than the entire integration segment.
    if (size > cut) {
        size = cut;
    }
    
    //checks if the integration step is larger than the size of the integration part
    if (size < dX) {
        size = dX;
        //dX = size / 10;
    }
    
    //number of threads
    int set = (int)(cut / size);

   
    
    //magic for thread initialization
    pthread_t tid [set];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    //magic for syncing threads
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    //creating threads
    potok_name array [set];
    for (int i = 0; i < set; i++) {
        (array [i]).id = i;             //the thread number
        (array [i]).size = size;        //integration segment
        (array [i]).mutex = &mutex;     //for synchronization
        
        
        //Ah here and so understandable :D
        pthread_create(&tid[i], &attr, potok, (void*) &(array[i]));
        
    }
    
    //waiting for threads to complete
    for (int i = 0; i < set; i++) {
        pthread_join(tid[i], NULL);
    }
    
    //counting the missing elements due to the whole number(INT) of threads
    for (double x = (double)set * size + dX; x <= cut; x += dX) {
        SUM += integ(x, dX);
    }

    //printf("\nSUM = %lg\ncut = %lg\nsize = %lg\nset = %i\n",cut, size, set);
    
    
    //Time of the entire program
    //2
    BOSStime = clock() - BOSStime;
    for (int i = 0; i < set; i++) {
        printf("The execution time of thread %i = %i milliseconds\n", i, array [i].time);
    }
    
    printf("\nExecution time of the entire program %i milliseconds\n", BOSStime);
    printf("\nIntegral x*dx = %lg\ncut = %lg\nsize = %lg\non %i streams\n", SUM, cut, size, set);
    pthread_mutex_destroy(&mutex);
    
    return 0;

}



//thread function
void* potok (void *array) {
    
    potok_name array_ = *((potok_name*) array);
    array_.time = clock();
    
    double data_sum = 0;

    //counting the integral
    for (double x = (double)array_.id * array_.size + dX; x <= ((double)array_.id + 1) * array_.size; x += dX) {
        //right here
        data_sum += integ(x, dX);
    }
    
    
    pthread_mutex_t mutex = (pthread_mutex_t) *(array_.mutex);

    pthread_mutex_lock(&mutex);
    
    /*
    printf("\data_sum %i = %i\n\n", array_.id, data_sum);
    //*/
    
    SUM += data_sum;

    pthread_mutex_unlock(&mutex);
    
    //saving the thread execution time
    ((potok_name*) array)->time = clock() - array_.time;
    
    pthread_exit(NULL);
}


//integral function
inline double integ(double x, double dx) {
    return x * dx;
}
