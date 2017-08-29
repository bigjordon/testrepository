#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	void (*print)();
	int (*add)(int, int);
	void *handle;
		if (argc < 2)
			return -1;
		handle = dlopen(argv[1], RTLD_LAZY);
		if (!handle) {
			printf("dlopen failed: %s\n", dlerror());
			return -1;
		}
		print = dlsym(handle, "print");
		if (!print) {
			printf("dlsym failed: %s\n", dlerror());
			return -1;
		}
		print();
		add = dlsym(handle, "add");
		if (!add) {
			printf("dlsym failed: %s\n", dlerror());
			return -1;
		}
		add(1, 2);
		dlclose(handle);
		return 0;
}
