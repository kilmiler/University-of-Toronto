#include <sys/stat.h> 
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int
main()
{
	int ret;
	char buffer[20];

	int fd = open("/tmp/file", O_RDONLY);
	assert(fd >= 0);
	
	ret = read(fd, buffer, 20);
	assert(ret >= 0);
	printf("%s", buffer);
	exit(0);
}
