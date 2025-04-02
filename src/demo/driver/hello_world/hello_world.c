#include <linux/version.h>
#include <linux/module.h>
#include <linux/printk.h>

/**
 * Create a Makefile,
 * run make. 
 * Load driver w/ `sudo insmod hello_world.ko`
 * unload driver w/ `sudo rmmod hello_world.ko`
 */

MODULE_LICENSE("GPL");

int init_module(void) {

    printk(KERN_INFO, "Hello (embedded) world!");
    return 0;
}


void cleanup_module(void) {

    printk(KERN_INFO, "Byebye (embedded) world!");
}