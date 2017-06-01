/*gcc -S asm_trylock.c*/
/*gcc -S -O  asm_trylock.c*/
#define LAST_FUNC_LEN 15
typedef struct {
	volatile unsigned int slock;
	char proc_name[LAST_FUNC_LEN];
	char last_func[LAST_FUNC_LEN];
	int last_line;
} __raw_spinlock_t;

static inline unsigned int x86_spin_trylock(__raw_spinlock_t * lock)
{
	int oldval;

	__asm__ __volatile__("\n"
			     "xchgl	%0, %1		\n\t"
			     :"=r"(oldval), "=m"(lock->slock)
			     :"0"(0)
			     :"memory");
	return (oldval <= 0);
}
int main()
{
	__raw_spinlock_t lock;
	x86_spin_trylock(&lock);
	return 0;
}
