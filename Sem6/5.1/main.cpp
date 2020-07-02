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


class potok_name {
public:
    int id = 0;
    int set = 0;
    pthread_mutex_t *mutex = NULL;
};

void* potok (void *array);


int SUM = 0;

int main (int argc, char *argv[])
{
    
    //
    //      Important N >= size
    //
    
    int N = 100;            // the number of summation 1,2,3,...,N
    int size = 4;           //number of threads
    int set = N / size;     //summation set
    
    if (N < size) {
        printf("\nW:N must be greater than size!!!!!!\n");
        return 1;
    }
    //magic for thread initialization
    pthread_t tid [size];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    //magic for syncing threads
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    //creating threads
    potok_name array [size];
    for (int i = 0; i < size; i++) {
        (array [i]).id = i;             //the thread number
        (array [i]).set = set;          //a set of numbers to sum up
        (array [i]).mutex = &mutex;     //for synchronization
        
        
        //Ah here and so understandable :D
        pthread_create(&tid[i], &attr, potok, (void*) &(array[i]));
        
    }
    
    //waiting for threads to complete
    for (int i = 0; i < size; i++) {
        pthread_join(tid[i], NULL);
    }
    
    
    pthread_mutex_destroy(&mutex);
    
    //adding up the missing numbers
    for (int i = set * size + 1; i <= N; i++) {
        SUM += i;
    }
    
    printf("\nThe sum of %i numbers on %i threads = %i\n\n", N, size, SUM);
    
    
    return 0;

}



void* potok (void *array) {
    
    potok_name array_ = *((potok_name*) array);
    
    
    int data_sum = 0;

    for (int i = array_.id * array_.set + 1; i <= (array_.id + 1) * array_.set; i++) {
        data_sum += i;
    }
    
    
    pthread_mutex_t mutex = (pthread_mutex_t) *(array_.mutex);

    pthread_mutex_lock(&mutex);
    
    /*
    printf("\data_sum %i = %i\n\n", array_.id, data_sum);
    //*/
    
    SUM += data_sum;

    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}
