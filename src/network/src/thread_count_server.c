#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>

/*

gcc thread_count_server.c -o server -pthread
./server


*/

int PORT = 8084;

// Get number of threads from /proc/self/status
int get_thread_count() {
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) return -1;

    char line[256];
    int threads = -1;

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "Threads: %d", &threads) == 1) {
            break;
        }
    }

    fclose(f);
    return threads;
}

void* handle_client(void *arg) {
    int client_fd = *(int*)arg;
    free(arg);

    int thread_count = get_thread_count();
    char response[64];
    snprintf(response, sizeof(response), "Threads: %d\n", thread_count);

    send(client_fd, response, strlen(response), 0);
    close(client_fd);
    return NULL;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 8) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        int *client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, NULL, NULL);
        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_fd);
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
