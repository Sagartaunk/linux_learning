/* This is a minimal copy of the `rust_minimals` sample module in the
 * linux kernel made to learn how `out-of-tree` modules are loaded into
 * the kernel as well as how to write them.
 *
 * This serves no function purpose except to print a few numbers.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>


int something(int x) {return x+1;}
EXPORT_SYMBOL(something);

int gpl(int x) {return x * 2 + 1;}
EXPORT_SYMBOL(gpl);

static int __init mod_init(void){
    pr_info("`mod` Module is loaded \n");
    int something[3] = {1,2,0};
    something[2] = 30;
    pr_info("Loaded values are %d, %d and %d \n", something[0], something[1], something[2]);
    pr_info("Exported {gpl}, {something}");
    /* The value `0` means the module loaded successfully any other value indicates and error in loading. */
    return 0;
}

static void __exit mod_exit(void) {
    pr_info("`mod` exited \n");
    return;
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sagar Taunk <sagartaunk@proton.me>");
MODULE_DESCRIPTION("C twin of rust_minimal");
