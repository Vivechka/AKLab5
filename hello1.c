#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

#include "hello1.h"

MODULE_AUTHOR("Bohdan Vasylenko IV-91");
MODULE_DESCRIPTION("Hello1 module. Prints str and operates list");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int i;

struct list {
	struct list_head tlist;
	ktime_t time;
};

static LIST_HEAD(my_list_head);

int print_hello(uint t)
{
	if (t > 10) {
		pr_err("ERROR! Parameter is incorrect\n");
		return -EINVAL;
	}

	if (t == 0 || (t >= 5 && t <= 10))
		pr_warn("WARNING! Parameter may cause errors\n");

	for (i = 0; i < t; i++) {
		struct list *n = kmalloc(sizeof(*n), GFP_KERNEL);

		n->time = ktime_get();

		pr_info("Hello, world!\n");

		n->time = ktime_get() - n->time;
		list_add(&n->tlist, &my_list_head);
	}

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void) {
	printk(KERN_INFO "Hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void) {
	struct list *md, *tmp;

	list_for_each_entry_safe(md, tmp, &my_list_head, tlist) {
		pr_info("%llx nanoseconds\n", md->time);
		list_del(&md->tlist);
		kfree(md);
	}
	BUG_ON(!list_empty(&my_list_head));
}

module_init(hello1_init);
module_exit(hello1_exit);