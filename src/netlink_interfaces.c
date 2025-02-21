#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <net/if.h>

#define BUFFER_SIZE 8192

/*
- gcc netlink_interfaces.c -o netlink_interfaces
- ./netlink_interfaces
*/

void list_interfaces() {
    int sock_fd;
    struct {
        struct nlmsghdr nlh;
        struct ifinfomsg ifm;
    } request;

    char buffer[BUFFER_SIZE];

    // Create Netlink socket
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (sock_fd < 0) {
        perror("socket");
        return;
    }

    // Prepare the request message
    memset(&request, 0, sizeof(request));
    request.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ifinfomsg));
    request.nlh.nlmsg_type = RTM_GETLINK;
    request.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
    request.ifm.ifi_family = AF_UNSPEC;

    // Send request to kernel
    if (send(sock_fd, &request, request.nlh.nlmsg_len, 0) < 0) {
        perror("send");
        close(sock_fd);
        return;
    }

    int count  = 1;

    // Read responses
    ssize_t len;
    while ((len = recv(sock_fd, buffer, sizeof(buffer), 0)) > 0) {
        struct nlmsghdr *nlh;
        for (nlh = (struct nlmsghdr *)buffer; NLMSG_OK(nlh, len); nlh = NLMSG_NEXT(nlh, len)) {
            if (nlh->nlmsg_type == NLMSG_DONE)
                break;
            if (nlh->nlmsg_type == NLMSG_ERROR) {
                fprintf(stderr, "Netlink error\n");
                close(sock_fd);
                return;
            }

            struct ifinfomsg *ifm = NLMSG_DATA(nlh);
            struct rtattr *attr = IFLA_RTA(ifm);
            int attr_len = IFLA_PAYLOAD(nlh);

            for (; RTA_OK(attr, attr_len); attr = RTA_NEXT(attr, attr_len)) {
                if (attr->rta_type == IFLA_IFNAME) {
                    printf("Interface (%d):  %s\n", count,  (char *)RTA_DATA(attr));
                    count++;
                }
            }
        }
    }

    close(sock_fd);
}

int main() {
    list_interfaces();
    return 0;
}