#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>


int sum(int a);
int multiply(int b);

int sum(int a) {
    return a+128;
}
int multiply(int b){
    return b*20;
}
EXPORT_SYMBOL(sum);
EXPORT_SYMBOL(multiply);

static int __init bad_init(void) {
    pr_info("Bad module is loaded \n");
    pr_info("This should stain the kernel \n");
    pr_info("Loaded sum with value 5 %d", sum(5));
    pr_info("Loaded multiply with value 5 %d", multiply(5));
    pr_info("EXPORTED {GPL} {SUM}");
    return 0;
};

static void __exit bad_exit(void) {
    pr_info("`mod` exited \n");
    return;
};


module_init(bad_init);
module_exit(bad_exit);
MODULE_LICENSE("BSD");
MODULE_AUTHOR("Sagar Taunk <sagartaunk@proton.me>");
MODULE_DESCRIPTION("C twin of rust_minimal");
