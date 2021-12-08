#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#include "hello1.h"

MODULE_AUTHOR("Bohdan Vasylenko IV-91");
MODULE_DESCRIPTION("Hello2 module use Hello1 module");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int t = 1;

module_param(t, uint, 0660);
MODULE_PARM_DESC(t, "Define how many times print message");

EXPORT_SYMBOL(t);

static int __init hello2_init(void) {
	return print_hello(t);
}

static void __exit hello2_exit(void) {
	printk(KERN_INFO "Hello2 module removed\n");
}

module_init(hello2_init);
module_exit(hello2_exit);