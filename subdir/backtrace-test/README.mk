the code

```
*((int*)(0)) = 5;

and 

my();
```
all will conduct a sigsegment fault

the diffrent `*((int*)(0)) = 5;`
use strace tool  will see the backtrace call (some mmap thing) and exit() call
```
write(1, "*********COMING HRER************"..., 35*********COMING HRER**************
) = 35
write(1, "\n", 1
)                       = 1
write(1, "\n", 1
)                       = 1
write(1, "\n", 1
)                       = 1
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=105630, ...}) = 0
mmap(NULL, 105630, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fb8bde2e000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p*\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=89696, ...}) = 0
mmap(NULL, 2185488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fb8bd643000
mprotect(0x7fb8bd659000, 2093056, PROT_NONE) = 0
mmap(0x7fb8bd858000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x15000) = 0x7fb8bd858000
close(3)                                = 0
munmap(0x7fb8bde2e000, 105630)          = 0
write(1, "backtrace() returned 12 addresse"..., 34backtrace() returned 12 addresses
) = 34
write(1, "./a.out() [0x400884]\n", 21./a.out() [0x400884]
)  = 21
write(1, "/lib/x86_64-linux-gnu/libc.so.6("..., 59/lib/x86_64-linux-gnu/libc.so.6(+0x354b0) [0x7fb8bd88e4b0]
) = 59
write(1, "./a.out() [0x400954]\n", 21./a.out() [0x400954]
)  = 21
write(1, "./a.out() [0x400975]\n", 21./a.out() [0x400975]
)  = 21
write(1, "./a.out() [0x40099d]\n", 21./a.out() [0x40099d]
)  = 21
write(1, "./a.out() [0x400996]\n", 21./a.out() [0x400996]
)  = 21
write(1, "./a.out() [0x400996]\n", 21./a.out() [0x400996]
)  = 21
write(1, "./a.out() [0x400996]\n", 21./a.out() [0x400996]
)  = 21
write(1, "./a.out() [0x400996]\n", 21./a.out() [0x400996]
)  = 21
write(1, "./a.out() [0x400a08]\n", 21./a.out() [0x400a08]
)  = 21
write(1, "/lib/x86_64-linux-gnu/libc.so.6("..., 73/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf0) [0x7fb8bd879830]
) = 73
write(1, "./a.out() [0x400779]\n", 21./a.out() [0x400779]
)  = 21
exit_group(11)                          = ?
+++ exited with 11 +++

```

while the `my()` call only conduct the sigsegment signal and the directly kill(may signal 9) the programm without the later
exit_group() system call
but if the Coredump file exit we can see all the call routine

```
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x44556677} ---
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 8), ...}) = 0
brk(NULL)                               = 0x972000
brk(0x993000)                           = 0x993000
write(1, "*********COMING HRER************"..., 35*********COMING HRER**************
) = 35
write(1, "\n", 1
)                       = 1
write(1, "\n", 1
)                       = 1
write(1, "\n", 1
)                       = 1
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=105630, ...}) = 0
mmap(NULL, 105630, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f5b13795000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p*\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=89696, ...}) = 0
mmap(NULL, 2185488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f5b12faa000
mprotect(0x7f5b12fc0000, 2093056, PROT_NONE) = 0
mmap(0x7f5b131bf000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x15000) = 0x7f5b131bf000
close(3)                                = 0
munmap(0x7f5b13795000, 105630)          = 0
--- SIGSEGV {si_signo=SIGSEGV, si_code=SEGV_MAPERR, si_addr=0x44556677} ---
+++ killed by SIGSEGV (core dumped) +++

```
