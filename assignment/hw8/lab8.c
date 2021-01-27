#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


double pi = 0.0;
int N=1000000,T=4;
pthread_mutex_t mut;


void *thread_function(void *arg){
    srand((unsigned)time(NULL));
    int hits = 0;
    for(int i=0; i<N; i++){
        double x = 2.0*rand()/RAND_MAX-1.0;
        double y = 2.0*rand()/RAND_MAX-1.0;

        if(x*x + y*y < 1.0){
            hits++;
        }
    }

    pthread_mutex_lock(&mut);
    pi = (pi + hits);
    pthread_mutex_unlock(&mut);
    return NULL;
}

int main(int argc, const char * argv[]) {

    pthread_t tid[T];
    int x[T];
    int scope;

/* get the default attributes */
    pthread_attr_t attr;
/* first inquire on the current scope */
    if ( (pthread_attr_getscope, attr , &scope ) != 0)
	fprintf(stderr, "Unable to get scheduling scope \n");
	else {
		if (scope == PTHREAD_SCOPE_PROCESS)
			printf("PTHREAD_SCOPE_PROCESS");
		else if (scope == PTHREAD_SCOPE_SYSTEM)
			printf("PTHREAD_SCOPE_SYSTEM");
		else
			fprintf (stderr, "Illegal scope \n");
		}
/* set the scheduling algorithm to PCS */
	pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
    
    for(int i=0;i<T;i++){
        x[i] = i;
        pthread_create(&tid[i], NULL, thread_function, &x[i]);
    }

    for(int i=0;i<T;i++){
        pthread_join(tid[i], NULL);
    }


     printf("The area of a unit circle is %f\n",pi/N);

     pthread_mutex_destroy(&mut);

    return 0;
}
