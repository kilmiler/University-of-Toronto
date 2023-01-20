#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* this program shows how thread output is interleaved in arbitrary order by the
 * thread scheduler. It also shows how threads share the address space (globals,
 * heap, etc.). */

/* initialize from user input */
/* notice how the loops variable is written by the main thread,
 * and read by the other two threads */
int loops;

/* demo of how heap is shared */
// int *count = NULL;

void *
T1(void *arg)
{
	int i;
	for (i = 0; i < loops; i++) {
		// count = malloc(sizeof(int));
		printf("w");
		printf("o");
		printf("r");
		printf("k");
		printf("e");
		printf("r");
		printf("1");
		printf("\n");		
	}
	return NULL;
}

void *
T2(void *arg)
{
	int i;
	for (i = 0; i < loops; i++) {
		// count[0] = 10;
		printf("w");
		printf("o");
		printf("r");
		printf("k");
		printf("e");
		printf("r");
		printf("2");
		printf("\n");
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: threads-print <loops>\n");
		exit(1);
	}
	loops = atoi(argv[1]);
	pthread_t p1, p2;
	/* create two threads, both threads run worker() */
	Pthread_create(&p1, NULL, T1, NULL);
	Pthread_create(&p2, NULL, T2, NULL);
	/* wait for the two threads to finish executing */
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);
	return 0;
}
