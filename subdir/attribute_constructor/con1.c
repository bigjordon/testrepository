static  __attribute__((constructor(102))) void file1()
{  
	printf("file1\n");
}
static  __attribute__((constructor())) void file1_1()
{  
	printf("file1_aaa1\n");
}
static  __attribute__((constructor())) void file1_2()
{  
	printf("file1_aaa2\n");
}
static  __attribute__((constructor())) void file1_3()
{  
	printf("file1_aaa3\n");
}
static  __attribute__((constructor())) void file1_4()
{  
	printf("file1_aaa4\n");
}
