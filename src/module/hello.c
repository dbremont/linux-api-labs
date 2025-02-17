// gcc -Wall -Werror -O2 -D__KERNEL__ -DMODULE -I /lib/modules/$(uname -r)/build/include -I /usr/src/linux-headers-$(uname -r)/arch/x86/include/generated -I /usr/src/linux-headers-$(uname -r)/arch/x86/include  -c module.c -o module.o


// hello_world.c
#include <linux/module.h>    // Required for all kernel modules
#include <linux/kernel.h>    // Required for KERN_INFO
#include <linux/init.h>      // Required for __init and __exit


// Module information
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Hello World kernel module");
MODULE_VERSION("1.0");

// The init function, called when the module is loaded
static int __init hello_world_init(void) {
    printk(KERN_INFO "Hello, World!\n");
    return 0;   // Return 0 means successful loading
}

// The exit function, called when the module is unloaded
static void __exit hello_world_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
}

// Register the init and exit functions
module_init(hello_world_init);
module_exit(hello_world_exit);
