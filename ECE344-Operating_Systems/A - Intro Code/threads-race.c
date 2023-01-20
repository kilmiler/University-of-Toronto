#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* this program shows two threads racing to update the counter global
 * variable */
volatile int counter = 0;
/* initialize from user input */
int loops;

void *
worker(void *arg)
{
	int i;
	/* increment counter by loops times */
	for (i = 0; i < loops; i++) {
		counter++;
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: threads <loops>\n");
		exit(1);
	}
	loops = atoi(argv[1]);
	pthread_t p1, p2;
	printf("Initial value : %d\n", counter);
	/* create two threads, both threads run worker() */
	Pthread_create(&p1, NULL, worker, NULL);
	Pthread_create(&p2, NULL, worker, NULL);
	/* wait for the two threads to finish executing */
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);
	/* print the value of the counter global variable */
	/* we expect the value of counter = 2 * loops */
	/* when loops is large, this may no longer be the case due to races */
	printf("Final value   : %d\n", counter);
	return 0;
}
