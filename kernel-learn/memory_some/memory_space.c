//#include <stdio.h>
/*gcc -E file.name*/
/*64 bits*/

/*#define __PAGE_OFFSET           _AC(0xffff880000000000, UL)*/
/* See Documentation/x86/x86_64/mm.txt for a description of the memory map. */
/* in file arch/x86/include/asm/page_64_types.h */
#define __PHYSICAL_MASK_SHIFT   46                                            
#define __VIRTUAL_MASK_SHIFT    47

/*
 * int file arch/x86/include/asm/page_types.h
 */
#define PAGE_SHIFT      12
#define PAGE_SIZE       (1UL << PAGE_SHIFT)
#define PAGE_MASK       (~(PAGE_SIZE-1))

#define __PHYSICAL_MASK         ((unsigned long)((1ULL << __PHYSICAL_MASK_SHIFT) - 1)) 
#define __VIRTUAL_MASK          ((1UL << __VIRTUAL_MASK_SHIFT) - 1)

#define PHYSICAL_PAGE_MASK     /*note signed*/ (((signed long)PAGE_MASK) & __PHYSICAL_MASK)
#define PTE_PFN_MASK            ((unsigned long/*pteval_t*/)PHYSICAL_PAGE_MASK)



/* source code
static inline unsigned long pte_pfn(pte_t pte)
{
        return (pte_val(pte) & PTE_PFN_MASK) >> PAGE_SHIFT; 
}

*/
static inline unsigned long pte_pfn(unsigned long pte)
{
        return (pte & PTE_PFN_MASK) >> PAGE_SHIFT; 
}	


int main()
{
	printf("         PAGE_MASK: %#18lx\n", PAGE_MASK);
	printf("   __PHYSICAL_MASK: %#18lx\n", __PHYSICAL_MASK);
	printf("    __VIRTUAL_MASK: %#18lx\n", __VIRTUAL_MASK);
	printf("PHYSICAL_PAGE_MASK: %#18lx\n", PHYSICAL_PAGE_MASK);
	printf("      PTE_PFN_MASK: %#18lx\n", PTE_PFN_MASK);
	printf("                    %#18lx\n", pte_pfn(0xffffffff81080293));
	return 0;
}
