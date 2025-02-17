#include <stdio.h>
#include <hidapi/hidapi.h>

// gcc -o mouse mouse.c -lhidapi-libusb

int main() {
    const char *device_path  = "/dev/hidraw4";  // Replace with the path to your device (e.g., /dev/hidraw3)
    hid_device *handle;

    // hid_set_debug(1);

    if (hid_init()) {
        printf("Failed to initialize HIDAPI\n");
        return 1;
    }

    // int vendor_id = 0x0c45;  // Replace with your vendor ID (e.g., 0x18F8)
    // int product_id = 0x6730; // Replace with your product ID (e.g., 0x0F99)

    // hid_device *handle = hid_open(vendor_id, product_id, NULL);  // Vendor ID: 0x18F8, Product ID: 0x0F99
        // Open the HID device using its path
    handle = hid_open_path(device_path);

    if (handle == NULL) {
        printf("Failed to open device: %ls\n", hid_error(handle));
        return 1;
    }


    unsigned char buf[256];
    while (1) {
        int res = hid_read(handle, buf, sizeof(buf));
        if (res > 0) {
            printf("Received data: ");
            for (int i = 0; i < res; i++)
                printf("%02X ", buf[i]);
            printf("\n");
        }
    }

    hid_close(handle);
    hid_exit();
    return 0;
}
