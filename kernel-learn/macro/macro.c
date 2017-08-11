#include <stdio.h>
#include <stdlib.h>




/* 
 * include/linux/kconfig.h add by me
 * Getting something that works in C and CPP for an arg that may or may
 * not be defined is tricky.  Here, if we have "#define CONFIG_BOOGER 1"
 * we match on the placeholder define, insert the "0," for arg1 and generate
 * the triplet (0, 1, 0).  Then the last step cherry picks the 2nd arg (a one).
 * When CONFIG_BOOGER is not defined, we generate a (... 1, 0) pair, and when
 * the last step cherry picks the 2nd arg, we get a zero.
 */

#define __ARG_PLACEHOLDER_1 0,
#define config_enabled(cfg) _config_enabled(cfg)
#define _config_enabled(value) __config_enabled(__ARG_PLACEHOLDER_##value)                                                                               
#define __config_enabled(arg1_or_junk) ___config_enabled(arg1_or_junk 1, 0)
#define ___config_enabled(__ignored, val, ...) val

#define IS_ENABLED(option) \
        (config_enabled(option) || config_enabled(option##_MODULE))

/*
 * IS_BUILTIN(CONFIG_FOO) evaluates to 1 if CONFIG_FOO is set to 'y', 0
 * otherwise. For boolean options, this is equivalent to
 * IS_ENABLED(CONFIG_FOO).
 */

#define XX 1
#define YY_MODULE
#define ZZ y
#define TT n
#define RR 0
#define CC 2

IS_ENABLED(XX)
IS_ENABLED(YY)
IS_ENABLED(ZZ)
IS_ENABLED(TT)
IS_ENABLED(RR)
IS_ENABLED(CC)

#if ZZ
0haha ZZ;
#endif

#if RR 
1haha RR;
#endif


#ifdef YY_MODULE 
2haha YY_MODULE;
#endif
