#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

int
main(int argc, char *argv[])
{
	char buffer[20];

	int fd = creat("/tmp/file", 0600);
	assert(fd >= 0);

	sprintf(buffer, "hello world\n");

	write(fd, buffer, strlen(buffer) + 1);

	close(fd);
	return 0;
}
