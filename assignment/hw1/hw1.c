/*
The first homework is mainly for your Linux and gcc getting ready, the common method is to use VMware and Ubuntu system.
The goal is to print "Hello World" in your linux terminal as well as a random number. Remember to change the srand to make it really random.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int a; //the output random value

	printf("Hello World!\r\n"); //print Hello World!

	srand((unsigned)time(NULL)); //set time as the seed of random value
	a = rand()%100; //output the random value between 0 and 99
	printf("%d\n",a);

	return 0;
};
