#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 20000

// For uint8_t, uint16_t, uint32_t, etc.
#include <stdint.h>

// For send and recv
#include <sys/types.h>
#include <sys/socket.h>
#include <stdbool.h>

int main() {
    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address information
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4243);  // Replace with the actual server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the actual server IP

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server!\n");

    ssize_t numChars;
    size_t bufferSize = 0;
    while (1) {
        char response[MAX_BUFFER_SIZE] = {0};
        // Receive and display the response from the server
        if (recv(sockfd, response, MAX_BUFFER_SIZE - 1, 0) == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        printf("Response: %s", response);
        char *buffer = calloc(MAX_BUFFER_SIZE, sizeof(char));
        // Read user input
        printf("Enter your command: ");
        numChars = getline(&buffer, &bufferSize, stdin);
        if (numChars == -1) {
            perror("Input error");
            break;
        }
        // Send the input to the server
        if (send(sockfd, buffer, strlen(buffer), 0) == -1) {
            perror("Send failed");
            exit(EXIT_FAILURE);
        }
        free(buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
