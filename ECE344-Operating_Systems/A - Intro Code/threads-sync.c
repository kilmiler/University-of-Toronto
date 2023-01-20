#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* this program shows how synchronization avoids the race in threads-race.c */
/* for synchronization, we use the m variable, which is a mutex lock (note that
 * m is a global variable) */ 
pthread_mutex_t m;
volatile int counter = 0;
/* initialize from user input */
int loops;

void *
worker(void *arg)
{
	int i;
	/* increment counter by loops times */
	for (i = 0; i < loops; i++) {
		Pthread_mutex_lock(&m); /* lock before accessing counter */
		counter++;
		Pthread_mutex_unlock(&m); /* unlock */
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
	/* initialize lock */
	Pthread_mutex_init(&m, NULL);
	/* create two threads, both threads run worker() */
	Pthread_create(&p1, NULL, worker, NULL);
	Pthread_create(&p2, NULL, worker, NULL);
	/* wait for the two threads to finish executing */
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);
	/* print the value of the counter global variable */
	/* we expect the value of counter = 2 * loops */
	printf("Final value   : %d\n", counter);
	return 0;
}
