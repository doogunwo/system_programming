#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void handle_get_request(int client_socket, const char *path) {
    // Handling GET request
    if (strcmp(path, "/") == 0) {
        path = "/index.html";
    }

    FILE *file = fopen(path + 1, "r");
    if (file == NULL) {
        // File not found
        char response[] = "HTTP/1.1 404 Not Found\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
        send(client_socket, response, sizeof(response), 0);
    } else {
        // File found, send content
        char response[1024];
        sprintf(response, "HTTP/1.1 200 OK\r\n\r\n");
        send(client_socket, response, strlen(response), 0);

        while (1) {
            size_t bytes_read = fread(response, 1, sizeof(response), file);
            if (bytes_read == 0) break;
            send(client_socket, response, bytes_read, 0);
        }

        fclose(file);
    }

    close(client_socket);
}

void handle_post_request(int client_socket, const char *path, const char *content) {
    // Handling POST request
    char command[1024];
    sprintf(command, ".%s", path);

    FILE *cgi_process = popen(command, "w");
    if (cgi_process == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    fprintf(cgi_process, "%s", content);
    pclose(cgi_process);

    char response[] = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>CGI Program Executed</h1></body></html>";
    send(client_socket, response, sizeof(response), 0);
    close(client_socket);
}

void handle_request(int client_socket) {
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("recv");
        return;
    }

    // Extracting method, path, and content from the request
    char method[10], path[256];
    sscanf(buffer, "%s %s", method, path);

    // Check if it's a GET or POST request
    if (strcmp(method, "GET") == 0) {
        handle_get_request(client_socket, path);
    } else if (strcmp(method, "POST") == 0) {
        char *content_start = strstr(buffer, "\r\n\r\n");
        if (content_start != NULL) {
            handle_post_request(client_socket, path, content_start + 4);
        } else {
            char response[] = "HTTP/1.1 400 Bad Request\r\n\r\n<html><body><h1>400 Bad Request</h1></body></html>";
            send(client_socket, response, sizeof(response), 0);
            close(client_socket);
        }
    } else {
        // Unsupported method
        char response[] = "HTTP/1.1 501 Not Implemented\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
        send(client_socket, response, sizeof(response), 0);
        close(client_socket);
    }
}

int main() {
    // ... (Same as the previous code)

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        handle_request(client_socket);
    }

    close(server_socket);

    return 0;
}
