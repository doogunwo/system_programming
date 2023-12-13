#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8070
#define BUFFER_SIZE 1024

void handle_get(int client_socket, const char *request);
void handle_post(int client_socket, const char *request);
void handle_file(int client_socket, const char *cgi_program, const char *content);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[BUFFER_SIZE];

    //소켓 설정
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    //서버 설정
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    //바인딩
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    //리슨 
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received == -1) {
            perror("Receive failed");
            close(client_socket);
            continue;
        }

        buffer[bytes_received] = '\0';

        if (strstr(buffer, "GET") != NULL) {
            handle_get(client_socket, buffer);
        } else if (strstr(buffer, "POST") != NULL) {
            handle_post(client_socket, buffer);
        }

        close(client_socket);
    }

    close(server_socket);

    return 0;
}

void handle_get(int client_socket, const char *request) {
    char requested_file[256];
    sscanf(request, "GET %s HTTP/1.1", requested_file);

    FILE *file = fopen(requested_file + 1, "r"); 
    if (file == NULL) {
        // get 요청으로 파일 가져다 주기
        const char *not_found_response = "HTTP/1.1 404 Not Found\r\n\r\n";
        send(client_socket, not_found_response, strlen(not_found_response), 0);
    } else {
        const char *ok_response = "HTTP/1.1 200 OK\r\n\r\n";
        send(client_socket, ok_response, strlen(ok_response), 0);

        char buffer[BUFFER_SIZE];
        size_t bytes_read;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
            send(client_socket, buffer, bytes_read, 0);
        }

        fclose(file);
    }
}

void handle_post(int client_socket, const char *request) {
    char cgi_program[256];
    sscanf(request, "POST %s HTTP/1.1", cgi_program);

    const char *content_length_start = strstr(request, "Content-Length: ") + strlen("Content-Length: ");
    size_t content_length;
    sscanf(content_length_start, "%zu", &content_length);

    char *content = (char *)malloc(content_length + 1);
    ssize_t bytes_received = recv(client_socket, content, content_length, 0);
    content[bytes_received] = '\0';

    handle_file(client_socket, cgi_program + 1, content);

    free(content);
}

void handle_file(int client_socket, const char *cgi_program, const char *content) {
    FILE *pipe_fp = popen(cgi_program, "w");
    if (pipe_fp == NULL) {
        const char *internal_server_error_response = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
        send(client_socket, internal_server_error_response, strlen(internal_server_error_response), 0);
        return;
    }

    fputs(content, pipe_fp);

    int pipe_status = pclose(pipe_fp);

    if (pipe_status == 0) {
        const char *ok_response = "HTTP/1.1 200 OK\r\n\r\n";
        send(client_socket, ok_response, strlen(ok_response), 0);
    } else {
        const char *internal_server_error_response = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
        send(client_socket, internal_server_error_response, strlen(internal_server_error_response), 0);
    }
}
