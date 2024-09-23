#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int main()
{
	fd_set read_fds;
	struct timeval timeout;
	int max_fd = 0;
	char buffer[100];

	// Initialize the set of file descriptors
	FD_ZERO(&read_fds);
	FD_SET(STDIN_FILENO, &read_fds);
	max_fd = STDIN_FILENO;

	// Set timeout to 5 seconds
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	printf("Waiting for input (timeout in 5 seconds) ...\n");

	// Wait for an input or a timeout
	
	int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);

	if (activity < 0) {
		perror("select error");
		return 1;
	} else if (activity == 0) {
		printf("Timeout occured! No data after 5 seconds.\n");
	} else {
		// Check if stdin is ready
		if (FD_ISSET(STDIN_FILENO, &read_fds)) {
		       fgets(buffer, sizeof(buffer), stdin);
		       printf("You entered: %s", buffer);
		}	       
	}

	return 0;
}
