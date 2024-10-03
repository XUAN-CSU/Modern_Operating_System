#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket, max_sd, activity, client_socket[MAX_CLIENTS];
    struct sockaddr_in address;
    fd_set read_fds;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_fd, 3);

    printf("Listening on port %d\n", PORT);

    // Initialize all client sockets to 0
    memset(client_socket, 0, sizeof(client_socket));

    while (1) {
        // Clear the socket set
        FD_ZERO(&read_fds);

        // Add server socket to set
        FD_SET(server_fd, &read_fds);
        max_sd = server_fd;

        // Add child sockets to set
        for (int i = 0; i < MAX_CLIENTS; i++) {
            new_socket = client_socket[i];
            if (new_socket > 0)
                FD_SET(new_socket, &read_fds);
            if (new_socket > max_sd)
                max_sd = new_socket;
        }

        // Wait for activity
        activity = select(max_sd + 1, &read_fds, NULL, NULL, NULL);

        if (activity < 0) {
            perror("select error");
            break;
        }

        // If something happened on the master socket, then it's an incoming connection
        if (FD_ISSET(server_fd, &read_fds)) {
            socklen_t addrlen = sizeof(address);
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection: socket fd %d\n", new_socket);

            // Add new socket to array of sockets
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        // Check all client sockets for incoming data
        for (int i = 0; i < MAX_CLIENTS; i++) {
            new_socket = client_socket[i];
            if (FD_ISSET(new_socket, &read_fds)) {
	    	socklen_t addrlen = sizeof(address);
                int valread = read(new_socket, buffer, sizeof(buffer));
                if (valread == 0) {
                    // Client disconnected
                    getpeername(new_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
                    printf("Client disconnected: socket fd %d\n", new_socket);
                    close(new_socket);
                    client_socket[i] = 0;
                } else {
                    buffer[valread] = '\0';
                    printf("Received: %s\n", buffer);
                }
            }
        }
    }

    return 0;
}
