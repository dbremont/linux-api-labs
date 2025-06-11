#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/*
gcc client.c -o client
*/

int PORT = 8084;

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = htonl(INADDR_LOOPBACK)  // 127.0.0.1 without inet_pton
    };

    sleep(10); // Ensure server is ready

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    sleep(10); // Allow connection to establish

    char buf[128];
    int n = read(sock, buf, sizeof(buf)-1);
    buf[n > 0 ? n : 0] = '\0';
    printf("%s", buf);

    close(sock);
    return 0;
}
