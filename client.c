#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4242

int main()
{
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Failed to create socket");
        return 1;
    }

    // Set up the server address
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddress.sin_addr)) <= 0) {
        perror("Invalid server address");
        close(serverSocket);
        return 1;
    }

    // Connect to the server
    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Failed to connect to the server");
        close(serverSocket);
        return 1;
    }

    // Set up the file descriptor set for select
    fd_set fds;
    int maxfd = (serverSocket > STDIN_FILENO) ? serverSocket : STDIN_FILENO;

    // Buffer to store received data
    char buffer[MAX_BUFFER_SIZE];

    // Main client loop
    while (1) {
        // Clear the file descriptor set
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(serverSocket, &fds);

        // Wait for activity on any of the file descriptors
        if (select(maxfd + 1, &fds, NULL, NULL, NULL) == -1) {
            perror("Select error");
            break;
        }

        // Check if there is data to read from stdin
        if (FD_ISSET(STDIN_FILENO, &fds)) {
            // Read from stdin
            memset(buffer, 0, sizeof(buffer));
            if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                // Send the input to the server
                if (send(serverSocket, buffer, strlen(buffer), 0) == -1) {
                    perror("Send error");
                    break;
                }
            } else {
                // Error or EOF on stdin, break the loop
                break;
            }
        }

        // Check if there is data to read from the server
        if (FD_ISSET(serverSocket, &fds)) {
            // Receive data from the server
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesRead = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead <= 0) {
                if (bytesRead == 0) {
                    printf("Server closed the connection\n");
                } else {
                    perror("Receive error");
                }
                break;
            } else {
                // Process the received data
                printf("Received from server: %s", buffer);
            }
        }
    }

    // Close the socket
    close(serverSocket);

    return 0;
}