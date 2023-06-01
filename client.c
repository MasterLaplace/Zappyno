#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

// pour uint8_t, uint16_t, uint32_t, etc.
#include <stdint.h>

// pour send et recv
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
    server_addr.sin_port = htons(8080);  // Replace with the actual server port
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Replace with the actual server IP

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server!\n");
    // Send a message to the server
    /*char message[] = "name1";
    if (send(sockfd, message, strlen(message), 0) == -1) {
        perror("Send failed");
        exit(EXIT_FAILURE);
    }


    // Receive a response from the server
    char buffer[MAX_BUFFER_SIZE];
    ssize_t num_bytes = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (num_bytes == -1) {
        perror("Receive failed");
        exit(EXIT_FAILURE);
    }
    buffer[num_bytes] = '\0';
    Package_t package = *(Package_t *) &buffer;
    printf("command_id: %d\n", package.command_id);
    printf("size: %d\n", ntohs(package.size));
    TeamIsFull teamIsFull = *(TeamIsFull *) &buffer[sizeof(Package_t)];
    printf("is_full: %d\n", teamIsFull.is_full);*/

    // Send a message to the server JoinCheckIA
    /*
     * uint8_t *buffer = calloc(size + sizeof(Package_t), sizeof(uint8_t));
    memcpy(buffer, package, sizeof(Package_t));
    memcpy(buffer + sizeof(Package_t), structure, size);
    // Send the buffer over the socket
    int bytes_sent = send(client->socket_fd, buffer, size + sizeof(Package_t), 0);
    if (bytes_sent == -1) {
        perror("send");
        exit(EXIT_FAILURE);
    }
     */
    ssize_t numChars;
    size_t bufferSize = 0;
    char *buffer = calloc(MAX_BUFFER_SIZE, sizeof(char));
    char response[MAX_BUFFER_SIZE] = {0};
    while (1) {
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

        // Receive and display the response from the server
        if (recv(sockfd, response, MAX_BUFFER_SIZE - 1, 0) == -1) {
            perror("Receive failed");
            exit(EXIT_FAILURE);
        }
        printf("Response: %s\n", response);
    }

    // Free the buffer
    free(buffer);


    // Close the socket
    close(sockfd);

    return 0;
}
