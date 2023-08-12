// This is a basic C web-server by markmental
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <sys/stat.h>

#define PORT 8000

static int serve_file(struct MHD_Connection *connection, const char *file_path, const char *mime_type) {
    struct MHD_Response *response;
    struct stat st;
    FILE *file = fopen(file_path, "rb");
    
    if (!file) {
        perror("File open error");
        return MHD_NO;
    }

    if (stat(file_path, &st) != 0) {
        perror("File stat error");
        fclose(file);
        return MHD_NO;
    }

    char *data = malloc(st.st_size);
    if (!data) {
        printf("Memory allocation error.\n");
        fclose(file);
        return MHD_NO;
    }

    fread(data, 1, st.st_size, file);
    fclose(file);

    response = MHD_create_response_from_buffer(st.st_size, data, MHD_RESPMEM_MUST_FREE);
    if (!response) {
        printf("Failed to create response from buffer.\n");
        free(data);
        return MHD_NO;
    }

    MHD_add_response_header(response, "Content-Type", mime_type);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

static enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection, const char *url,
                                       const char *method, const char *version, const char *upload_data,
                                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) {
        printf("Not a GET request.\n");
        return MHD_NO;
    }

    char file_path[1024];

    if (strcmp(url, "/") == 0) {
        strcpy(file_path, "./index.html");
        if (access(file_path, F_OK) != -1) {
            printf("Detected HTML file for root. About to call serve_file.\n");
            return serve_file(connection, file_path, "text/html");
        }
    } else {
        snprintf(file_path, sizeof(file_path), ".%s", url);
    }

    printf("Attempting to serve: %s\n", file_path);

    char temp_path[1024];
    strcpy(temp_path, file_path);

    // Check for HTML file
    strcat(temp_path, ".html");
    if (access(temp_path, F_OK) != -1) {
        printf("Detected HTML file. About to call serve_file.\n");
        return serve_file(connection, temp_path, "text/html");
    }
    strcpy(temp_path, file_path); // Reset temp_path

    // Check for CSS file
    strcat(temp_path, ".css");
    if (access(temp_path, F_OK) != -1) {
        printf("Detected CSS file. About to call serve_file.\n");
        return serve_file(connection, temp_path, "text/css");
    }
    strcpy(temp_path, file_path); // Reset temp_path

    // Check for PNG file
    strcat(temp_path, ".png");
    if (access(temp_path, F_OK) != -1) {
        printf("Detected PNG file. About to call serve_file.\n");
        return serve_file(connection, temp_path, "image/png");
    }
    strcpy(temp_path, file_path); // Reset temp_path

    // Check for JPG file
    strcat(temp_path, ".jpg");
    if (access(temp_path, F_OK) != -1) {
        printf("Detected JPG file. About to call serve_file.\n");
        return serve_file(connection, temp_path, "image/jpeg");
    }
    strcpy(temp_path, file_path); // Reset temp_path

    // Check for JPEG file
    strcat(temp_path, ".jpeg");
    if (access(temp_path, F_OK) != -1) {
        printf("Detected JPEG file. About to call serve_file.\n");
        return serve_file(connection, temp_path, "image/jpeg");
    }

    printf("No matching file type detected.\n");
    return MHD_NO;
}


int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &request_handler, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    getchar(); // Wait for user input to terminate

    MHD_stop_daemon(daemon);
    printf("\nServer stopped.\n");
    return 0;
}
