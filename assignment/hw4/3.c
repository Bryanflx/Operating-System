#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>    
#include<unistd.h>       
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(void)
{
	int n,d;
	printf("input n and d\n");
	scanf("%d%d",&n,&d);
	

	int k=0;
	
	int fd[2];
	int x,y;
	pid_t pid;
	
	/* create the pipe */
	if (pipe(fd) == 1) {
		perror("Pipe failed");
		return -1;
	}
	
	
	/* fork a child process */
	pid = fork();
	if(pid<0){ 			/* error occured */
		perror("Fork Failed");
		return 1;
	}
	else if (pid > 0) {		/* parent process*/
	
		close(fd[WRITE_END]);
		
		/* read data from the pipe */
		for (k=0;k<n;++k){
			read(fd[READ_END], &x,sizeof(int));
			printf("%d ",x);
		}
		printf("\n");
		
		/* close the read end */
		close(fd[READ_END]);
		exit(0);
	}
	else { 			/* child process*/
		
		close(fd[READ_END]);
		
		//write data to pipe
		for (k=0;k<n;++k){
			y = k*d;
			write(fd[WRITE_END], &y, sizeof(int));
		}
		/* close the write end */
		close(fd[WRITE_END]);
		exit(0);
	}
	return 0;
}
