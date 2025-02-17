#include <stdio.h>
#include <stdlib.h>
#include <hidapi/hidapi.h>

int main() {
    struct hid_device_info *devs, *dev;

    // Initialize the HIDAPI library
    if (hid_init()) {
        printf("Failed to initialize HIDAPI\n");
        return 1;
    }

    // Enumerate all connected HID devices
    devs = hid_enumerate(0x0, 0x0);  // Pass 0x0 for both to get all devices

    // Loop through the devices and print those that match the vendor/product ID
    dev = devs;
    while (dev) {
        if (dev->vendor_id == vendor_id && dev->product_id == product_id) {
            printf("Found device:\n");
            printf("Vendor ID: 0x%04X\n", dev->vendor_id);
            printf("Product ID: 0x%04X\n", dev->product_id);
            printf("Path: %s\n", dev->path);
            printf("Serial Number: %ls\n", dev->serial_number);
            printf("Manufacturer: %ls\n", dev->manufacturer_string);
            printf("Product: %ls\n", dev->product_string);
        }
        dev = dev->next;
    }

    // Free the device list
    hid_free_enumeration(devs);

    // Finalize the HIDAPI library
    hid_exit();

    return 0;
}
