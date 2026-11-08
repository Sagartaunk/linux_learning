/* User for `mod.c` defined within this repository */

#include <linux/module.h>
#include <linux/kernel.h>

extern int something(int);
extern int gpl(int);

static int __init initialise(void) {
    pr_info("Loaded mod.c \n Something:{%d}, gpl:{%d}", something(22), gpl(10));
    return 0;
};
static void __exit exxit(void) {
    pr_info("Exited the module");
    return;
};
module_init(initialise);
module_exit(exxit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Caller for mod.c");
