#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/* this program shows the benefits of CPU virtualization */
/* it shows that large number of copies of this program can be run, even though
 * there are a limited number of CPUs */
int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: cpu <string>\n");
		exit(1);
	}
	char *str = argv[1];

	while (1) {
		printf("%s\n", str);
		Spin(1);
	}
	return 0;
}
