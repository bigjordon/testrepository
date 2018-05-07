#define NUM 5
#define STR1(R)  #R  
#define STR2(R)  STR1(R)  
"STR1(NUM)" STR1(NUM)
"STR2(NUM)" STR2(NUM)
"STR1(2)"   STR1(2)
"STR2(2)"   STR2(2)
"STR1(STR1-(NUM))"   STR1(STR1-(NUM))  不可嵌套

char *string = "start  " STR2(NUM) " end";
