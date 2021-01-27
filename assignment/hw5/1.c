#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


double pi = 0.0;
int N=1000000,T=4; //set the number of worker threads and sampling points
pthread_mutex_t mut; //set mutex to protect the shared variable


void *thread_function(void *arg){
    unsigned int seed = 123;
    int hits = 0;
    for(int i=0; i<N; i++){
        double x = 2.0*rand_r(&seed)/RAND_MAX-1.0; //calculate pi by Monte Carlo method
        double y = 2.0*rand_r(&seed)/RAND_MAX-1.0;

        if(x*x + y*y < 1.0){
            hits++;
        }
    }

    pthread_mutex_lock(&mut);
    pi = (pi + hits); //shared variable kept by each thread
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main(int argc, const char * argv[]) {

    pthread_t thread[T];
    int x[T];

/*
create and set the N parallel worker threads, run thread_function in each thread
*/
    for(int i=0;i<T;i++){
        x[i] = i;
        pthread_create(&thread[i], NULL, thread_function, &x[i]);
    }
    
    for(int i=0;i<T;i++){
        pthread_join(thread[i], NULL);
    }

     pi = pi/N;
     printf("The area of a unit circle is %f\n",pi);

    return 0;
}
