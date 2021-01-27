#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    
#include <unistd.h>       
#include <sys/mman.h>
#include <sys/wait.h>

/*
store an arithmetic sequence of length n at addr, the first element 
is 0 and each following element has the value of kd, 
where k is the element number (k=0 to n-1)
*/

/*
create the sequence and store it
*/

void write_data(void* addr,int n,int d){
	int* p= addr;
	int k=0;
	for(k=0;k<n;++k){
		p[k]=k*d;
	}
}


/*
obtain the sequence from the shared memory and print it.
*/

void read_data(void* addr,int n,int d){
	int* p= addr;
	int k=0;
	for(k=0;k<n;++k){
		printf("%d ",p[k]);
	}
	printf("\n");
}


int main(int argc, char *argv[]){
	int d=atoi(argv[1]);
	int n=atoi(argv[2]);

	/*
	create an anonymous shared memory by using mmap
	 void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);

	*/
	void* ptr = mmap(NULL, n*sizeof(int), PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED, -1, 0);
	
	//printf ("The shared momery address is %p\n",&ptr);
	
	if (ptr==NULL) {
		printf("mmap failed");
		exit(-1);
	}
	
	pid_t pid =fork();
	if (pid < 0){
		printf("fork failed");
	}
	
	if (pid==0){   		//child process
		write_data(ptr,n,d);
		
		printf ("The address in child process is %p\n",&ptr);
		exit(0); 
	}
	else{        			//parent process
		wait(NULL);  		//wait for the child to exit
		printf ("The address in parent process is %p\n",&ptr);
		read_data(ptr,n,d);
	}
	munmap(ptr,n*sizeof(int));     //release the space of shared memory
	return 0;
}
