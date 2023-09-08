#include <module-example/version.h>

#include <zephyr/kernel.h>

void module_example_print_version(void) {
	printk("Module example version: %s\n", MODULE_EXAMPLE_VERSION);
}