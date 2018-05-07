#define NUM 5
#define STR1(R)  #R  
#define STR2(R)  STR1(R)  
STR1(NUM)
STR2(NUM)
char *string = "start  " STR2(NUM) " end";
