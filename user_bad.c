/* User for `bad.c` defined within this repository */

#include <linux/module.h>
#include <linux/kernel.h>

extern int sum(int);
extern int multiply(int);

static int __init initialise(void) {
    pr_info("Loaded bad.c \n add:{%d}, multiply:{%d}", sum(22), multiply(10));
    return 0;
};
static void __exit exxit(void) {
    pr_info("Exited the module");
    return;
};
module_init(initialise);
module_exit(exxit);

MODULE_LICENSE("BSD");
MODULE_DESCRIPTION("Caller for bad.c");
