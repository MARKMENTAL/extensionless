#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/types.h>

#define PORT 8000
#define BUFFER_SIZE 4096
#define RESPONSE_HEADER_SIZE 1024
#define MAX_FILE_SIZE 1048576 // 1MB

int serve_file(int client_fd, const char *file_path, const char *mime_type);
int try_serve_file(int client_fd, const char *url, const char *extension, const char *mime_type);
void handle_http_request(int client_fd);
void send_404(int client_fd);

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Socket listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            perror("Accept failed");
            continue;
        }

        handle_http_request(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}

void handle_http_request(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_fd, buffer, BUFFER_SIZE);

    char *method = strtok(buffer, " ");
    char *url = strtok(NULL, " ");

    if (strcmp(method, "GET") != 0) {
        printf("Only GET method is supported.\n");
        return;
    }

    if (strcmp(url, "/") == 0) {
        if (!try_serve_file(client_fd, url, "index.html", "text/html")) {
            send_404(client_fd);
        }
        return;
    }

    if (!try_serve_file(client_fd, url, ".html", "text/html") &&
        !try_serve_file(client_fd, url, ".css", "text/css") &&
        !try_serve_file(client_fd, url, ".png", "image/png") &&
        !try_serve_file(client_fd, url, ".jpg", "image/jpeg") &&
        !try_serve_file(client_fd, url, ".jpeg", "image/jpeg")) {
        send_404(client_fd);
    }
}

int try_serve_file(int client_fd, const char *url, const char *extension, const char *mime_type) {
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), ".%s%s", url, extension);

    if (access(file_path, F_OK) != -1) {
        return serve_file(client_fd, file_path, mime_type);
    }
    return 0; // File not found
}

int serve_file(int client_fd, const char *file_path, const char *mime_type) {
    struct stat st;
    if (stat(file_path, &st) < 0 || st.st_size > MAX_FILE_SIZE) {
        send_404(client_fd);
        return -1;
    }

    int fd = open(file_path, O_RDONLY);
    if (fd < 0) {
        perror("File open failed");
        send_404(client_fd);
        return -1;
    }

    char response_header[RESPONSE_HEADER_SIZE];
    snprintf(response_header, RESPONSE_HEADER_SIZE,
             "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\n\r\n",
             mime_type, st.st_size);

    write(client_fd, response_header, strlen(response_header));

    char *file_buffer = malloc(st.st_size);
    if (!file_buffer) {
        printf("Memory allocation failed.\n");
        close(fd);
        send_404(client_fd);
        return -1;
    }

    read(fd, file_buffer, st.st_size);
    write(client_fd, file_buffer, st.st_size);
    free(file_buffer);

    close(fd);
    return 1; // File served successfully
}

void send_404(int client_fd) {
    const char *response = "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n";
    write(client_fd, response, strlen(response));
}

