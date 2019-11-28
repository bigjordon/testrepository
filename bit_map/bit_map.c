#include <stdio.h>
#include <stdlib.h>

#define BITS_PER_LONG 64
#define NR_CPUS 64

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#define BITS_PER_BYTE           8
#define BITS_TO_LONGS(nr)       DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))   

#define MASK_DECLARE_1(x)       [x+1][0] = (1UL << (x))               
#define MASK_DECLARE_2(x)       MASK_DECLARE_1(x), MASK_DECLARE_1(x+1)
#define MASK_DECLARE_4(x)       MASK_DECLARE_2(x), MASK_DECLARE_2(x+2)
#define MASK_DECLARE_8(x)       MASK_DECLARE_4(x), MASK_DECLARE_4(x+4)

const unsigned long cpu_bit_bitmap[BITS_PER_LONG+1][BITS_TO_LONGS(NR_CPUS)] = {

        MASK_DECLARE_8(0),      MASK_DECLARE_8(8),
        MASK_DECLARE_8(16),     MASK_DECLARE_8(24),
        MASK_DECLARE_8(32),     MASK_DECLARE_8(40),
        MASK_DECLARE_8(48),     MASK_DECLARE_8(56),
};

static const unsigned long  *get_cpu_mask(unsigned int cpu)       
{                                                                        
        const unsigned long *p = cpu_bit_bitmap[1 + cpu % BITS_PER_LONG];
        p -= cpu / BITS_PER_LONG;                                        
        return (unsigned long*)(p);                                            
}


int main(void)
{
	
	return 0;
}
