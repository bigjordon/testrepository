#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int _memmerytotal_0_int = 0x40000000;
	int _memmerytotal_1_int = 0x3fffffff;
	unsigned long _memmerytotal_0_ulong = 0x40000000;
	unsigned long _memmerytotal_1_ulong = 0x3fffffff;
	int more = 0;

	int a = 1234567; /* any number less 2G (2^31) */
	if (argc == 2)
		more = atoi(argv[1]);

	printf("a: %d\n", a);
	printf("more : %d can get from argv1, default is 0\n", more);
	printf("_memmerytotal_0_int: %d\n", _memmerytotal_0_int);
	printf("_memmerytotal_1_int: %d\n", _memmerytotal_1_int);
	printf("_memmerytotal_0_ulong: %lu\n", _memmerytotal_0_ulong);
	printf("_memmerytotal_1_ulong: %lu\n", _memmerytotal_1_ulong);

	if (a < _memmerytotal_0_int + _memmerytotal_1_int + more) {
		printf("a: %d is %s than total: %d when `more` is %d\n", a, "less", 
			_memmerytotal_0_int + _memmerytotal_1_int + more, more);
	} else  if (a < _memmerytotal_0_int + _memmerytotal_1_int + more){
		printf("a: %d is %s than total: %d when `more` is %d\n", a, "equal", 
			_memmerytotal_0_int + _memmerytotal_1_int + more, more);
	} else {
		printf("a: %d is %s than total: %d when `more` is %d\n", a, "bigger", 
			_memmerytotal_0_int + _memmerytotal_1_int + more, more);
	}
	
	if (a < _memmerytotal_0_ulong + _memmerytotal_1_ulong + more) {
		printf("a: %d is %s than total: %lu when `more` is %d\n", a, "less", 
			_memmerytotal_0_ulong + _memmerytotal_1_ulong + more, more);
	} else  if (a < _memmerytotal_0_ulong + _memmerytotal_1_ulong + more){
		printf("a: %d is %s than total: %lu when `more` is %d\n", a, "equal", 
			_memmerytotal_0_ulong + _memmerytotal_1_ulong + more, more);
	} else {
		printf("a: %d is %s than total: %lu when `more` is %d\n", a, "bigger", 
			_memmerytotal_0_ulong + _memmerytotal_1_ulong + more, more);
	}
	return 0;
}


#if 0
        int offset = (addr) - vma->vm_start;
        int i_mt = nm_mem->nm_if_pool->_memtotal;
        int r_mt = nm_mem->nm_ring_pool->_memtotal;
        int b_mt = nm_mem->nm_buf_pool->_memtotal;
        int index, ofs;
        if (offset < i_mt) {
		do-some-thing():
        } else if (offset < (i_mt + r_mt)) {
		do-some-thing():
        } else if (offset < (i_mt + r_mt + b_mt)) { /* this line has someproble when
						       i_mt + r_mt + b_mt is more than 2G */
		do-some-thing():
        } else 
                return 0;

	/**
	 * this code leet is a vma->vm_ops .access callback int the kernel space
	 * when the user space programm use `mmap()` map ( and PNF mapping)the kernel meomory to
	 * the process's virtual memory space. According the kernel code comments:
	 *
	 * -called by access_process_vm when get_user_pages() fails, typically
	 * -for use by special VMAs that can switch between memory and hardware
	 * -  kernel 3.16.44  include/linux/mm.h struct vm_operations_struct
	 *
	 * -If the source page was a PFN mapping, we don't have
	 * -a "struct page" for it. We do a best-effort copy by
	 * -just copying from the original user address. If that
	 * -fails, we just zero-fill it. Live with it.
	 * - kernel 3.16.44 mm/memory.c cow_user_page comments
	 *
	 * gdb attach a process the kernel will call __access_remote_vm to access the
	 * process's mmaped kernel memory use access method
	*/
#endif
