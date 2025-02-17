#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <linux/hidraw.h>

// gcc -o mouse mouse.c -lhidapi-libusb
//

int main() {
    const char *device_path = "/dev/hidraw3"; // Path for the mouse (from dmesg)
    int fd;
    char name[256];  // Buffer to store device name
    struct hidraw_devinfo info;

    // Open the HID device
    fd = open(device_path, O_RDWR);
    if (fd == -1) {
        perror("Unable to open device");
        return 1;
    }

    // Get the device name
    if (ioctl(fd, HIDIOCGRAWNAME(sizeof(name)), name) == -1) {
        perror("Unable to get device name");
        close(fd);
        return 1;
    }

    printf("Device name: %s\n", name);

    // Get device information (vendor ID and product ID)
    if (ioctl(fd, HIDIOCGRAWINFO, &info) == -1) {
        perror("Unable to get device info");
        close(fd);
        return 1;
    }

    printf("Device vendor ID: 0x%04X\n", info.vendor);
    printf("Device product ID: 0x%04X\n", info.product);

    // Try reading raw input data from the device (e.g., mouse movement or clicks)
    unsigned char buf[256];  // Adjust buffer size as needed
    int bytesRead;
    while (1) {
        bytesRead = read(fd, buf, sizeof(buf));
        if (bytesRead < 0) {
            perror("Error reading from HID device");
            close(fd);
            return 1;
        }

        // Process the input data (depending on the format)
        printf("Read %d bytes\n", bytesRead);
        for (int i = 0; i < bytesRead; i++) {
            printf("0x%02X ", buf[i]);
        }
        printf("\n");

        // Add conditions to break out of the loop or handle specific inputs
    }

    // Feature reports might not be supported, so skip this section
    // unsigned char report[256];  // Adjust size based on device capability
    // int res = ioctl(fd, HIDIOCGFEATURE(256), report);
    // if (res == -1) {
    //     perror("Unable to get feature report");
    // } else {
    //     printf("Received feature report\n");
    //     for (int i = 0; i < res; i++) {
    //         printf("0x%02X ", report[i]);
    //     }
    //     printf("\n");
    // }

    close(fd);  // Close the device
    return 0;
}