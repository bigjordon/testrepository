static  __attribute__((constructor(102))) void file2()
{  
	printf("file2\n");
}
static  __attribute__((constructor())) void file2_0()
{  
	printf("file2_aaa0\n");
}

static  __attribute__((constructor())) void file2_1()
{  
	printf("file2_aaa1\n");
}
static  __attribute__((constructor())) void file2_2()
{  
	printf("file2_aaa2\n");
}
static  __attribute__((constructor())) void file2_3()
{  
	printf("file2_aaa3\n");
}
