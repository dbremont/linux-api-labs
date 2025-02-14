#include <stdio.h>
#include <fcntl.h>
#include <linux/hdreg.h>
#include <sys/ioctl.h>

int main() {
    int fd = open("/dev/sda", O_RDONLY);
    struct hd_driveid id;
    
    if (ioctl(fd, HDIO_GET_IDENTITY, &id) == 0) {
        printf("Model: %s\n", id.model);
        printf("Firmware: %s\n", id.fw_rev);
    } else {
        perror("ioctl");
    }

    close(fd);
    return 0;
}
