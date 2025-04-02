#include <linux/module.h>
#include <linux/version.h>
#include <linux/proc_fs.h>


#define LICENSE "GPL"
#define DRIVER_AUTHOR "Thorsten Suckow-Homberg <thorsten@suckow-homberg.de>"
#define DRIVER_NAME  "PrtDrvr"


MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(DRIVER_AUTHOR);


static unsigned int prtdrvr_major = 0;


ssize_t prtdrvr_write(struct file *filp, const char *buf, size_t count, loff_t *t) {

	int i = 1;
	struct task_struct *parent = current->real_parent;

	printk(KERN_INFO "%s_write called. Here's the required  information according to ES3.1:\n"
					 "1. [caller]: %s; PID: %d; start-time: %llu\n",
		DRIVER_NAME,
		current->comm, current->pid, current->real_start_time
	);



	while (true) {
		pid_t pid = parent->pid;

		if (pid == 1) {
			printk(
				KERN_INFO "3.[systemd] found %s; PID: %d; start-time: %llu\n",
				parent->comm, pid, parent->real_start_time
			);
			printk(KERN_INFO "(omitting IDLE/SWAPPER. Done!)");

			break;
		} else {
			printk(
				KERN_INFO "    2.%d [parent] %s; PID: %d; start-time: %llu\n",
				i, parent->comm, pid, parent->real_start_time
			);
		}

		parent = parent->real_parent;
		i++;
	}



	return count;
}


struct file_operations prtdrvr_fops = {
	.owner   = THIS_MODULE,
	.write   = prtdrvr_write
};


int init_module() {
	int result = register_chrdev(prtdrvr_major, DRIVER_NAME, &prtdrvr_fops);

    if (result < 0) {
    	return result;
    }

    // assign major number from kernel
    if (prtdrvr_major == 0) {
        prtdrvr_major = result;
    }

	// newlines help with flushing ob
	printk(KERN_INFO "%s@%d driver loaded\n", DRIVER_NAME, prtdrvr_major);
	return 0;
}


void cleanup_module() {
	unregister_chrdev(prtdrvr_major, DRIVER_NAME);
	printk(KERN_INFO "%s@%d driver unloaded. Bybebye!\n", DRIVER_NAME, prtdrvr_major);
	return;
}