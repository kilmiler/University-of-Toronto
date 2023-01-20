#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common.h"

/* the point of this program is to show the benefits of memory virtualzation */

/* when we run two copies of the program, we will see that the pointer p has the
 * same value in both programs, yet *p in the two copies of the program has
 * different values. In other words, the contents of the memory in the two
 * programs at the SAME memory address are DIFFERENT, even though the programs
 * are running concurrently! */ 

int
main(int argc, char *argv[])
{
	int *p;	// memory for pointer is on "stack"
	if (argc != 2) {
		fprintf(stderr, "usage: mem <value>\n");
		exit(1);
	}
	/* we make p point to memory on the heap */
	/* when we run multiple copies of this program, p will have the same
	 * value because the heap memory generally starts at the same memory
	 * address. 
	 * To disable ASLR, run the program as follows: 
	 *   setarch x86_64 -R ./mem <value>
	 */
	p = malloc(sizeof(int)); // malloc'd memory is on "heap"
	assert(p != NULL);
	/* now we will set the value of the heap by dereferencing p */
	*p = atoi(argv[1]);
	while (1) {
		Spin(1);
		*p = *p + 1; /* keep incrementing the value in the heap */
		printf("(pid: %d) address of p: 0x%lx, value of p: %d\n",
		       getpid(), (unsigned long)p, *p);
	}

	return 0;
}
