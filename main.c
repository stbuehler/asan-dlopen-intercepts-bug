#include <dlfcn.h>
#include <stdio.h>

typedef void (*run_fn)();

int main() {
	void *plugin = dlopen("./plugin.so", RTLD_NOW|RTLD_GLOBAL);
	run_fn fn = (run_fn) dlsym(plugin, "run");
	printf("Found plugin run function: %p\n", fn);
	(*fn)();
}
